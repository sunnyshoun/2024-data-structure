#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    int key;
    int degree;
    struct Node *parent, *child, *left, *right;
    int mark;
} Node;

typedef struct FHeap {
    Node *min;
    int n;
} FHeap;

Node* create_node(int key) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->degree = 0;
    node->parent = node->child = NULL;
    node->left = node->right = node;
    node->mark = 0;
    return node;
}

FHeap* create_heap() {
    FHeap *heap = (FHeap*)malloc(sizeof(FHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

void insert(FHeap *heap, int key) {
    Node *node = create_node(key);
    if (heap->min == NULL) {
        heap->min = node;
    } else {
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right = node;
        node->right->left = node;
        if (node->key < heap->min->key) {
            heap->min = node;
        }
    }
    heap->n++;
}

void link(FHeap *heap, Node *y, Node *x) {
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (x->child == NULL) {
        x->child = y;
        y->right = y->left = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right = y;
        y->right->left = y;
    }
    x->degree++;
    y->mark = 0;
}

void consolidate(FHeap *heap) {
    int maxDegree = (int)(log(heap->n) / log(2)) + 1;
    Node* A[maxDegree];
    for (int i = 0; i < maxDegree; i++) A[i] = NULL;
    
    Node *x = heap->min;
    Node *start = x;
    do {
        Node *next = x->right;
        int d = x->degree;
        while (A[d] != NULL) {
            Node *y = A[d];
            if (x->key > y->key) {
                Node *temp = x;
                x = y;
                y = temp;
            }
            link(heap, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        x = next;
    } while (x != start);
    
    heap->min = NULL;
    for (int i = 0; i < maxDegree; i++) {
        if (A[i] != NULL) {
            if (heap->min == NULL) {
                heap->min = A[i];
            } else {
                A[i]->left = heap->min;
                A[i]->right = heap->min->right;
                heap->min->right = A[i];
                A[i]->right->left = A[i];
                if (A[i]->key < heap->min->key) {
                    heap->min = A[i];
                }
            }
        }
    }
}

Node* extract_min(FHeap *heap) {
    Node *z = heap->min;
    if (z != NULL) {
        if (z->child != NULL) {
            Node *x = z->child;
            do {
                Node *next = x->right;
                x->left = heap->min;
                x->right = heap->min->right;
                heap->min->right = x;
                x->right->left = x;
                x->parent = NULL;
                x = next;
            } while (x != z->child);
        }
        z->left->right = z->right;
        z->right->left = z->left;
        if (z == z->right) {
            heap->min = NULL;
        } else {
            heap->min = z->right;
            consolidate(heap);
        }
        heap->n--;
    }
    return z;
}

void print_heap(Node *node) {
    if (node == NULL) return;
    Node *start = node;
    do {
        printf("%d ", node->key);
        if (node->child != NULL) {
            print_heap(node->child);
        }
        node = node->right;
    } while (node != start);
}

int main() {
    FHeap *heap = create_heap();
    char command[20];
    int key, value;

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            insert(heap, key);
        } else if (strcmp(command, "extract-min") == 0) {
            extract_min(heap);
        } else if (strcmp(command, "exit") == 0) {
            break;
        }
    }
    print_heap(heap->min);
    return 0;
}
