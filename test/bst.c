#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BSTNode{
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} Node;

typedef struct BST{
    Node* root;
} BST;

BST* newBST(){
    BST* bst = malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

void insert(BST* bst, int key){
    Node* newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    if(!bst->root){
        bst->root = newNode;
    }
    else{
        Node* cur = bst->root;
        while(true){
            if(key > cur->key){
                if(!cur->right){
                    cur->right = newNode;
                    return;
                }
                cur = cur->right;
            }
            else{
                if(!cur->left){
                    cur->left = newNode;
                    return;
                }
                cur = cur->left;
            }
        }
    }
}

void dfs(Node* node){
    if(!node) return;
    printf("%d ", node->key);
    dfs(node->left);
    dfs(node->right);
    free(node);
}

int main(){
    int N, k;
    while(scanf("%d", &N) != EOF){
        BST* bst = newBST();
        for(int i=0; i<N; i++){
            scanf("%d", &k);
            insert(bst, k);
        }
        dfs(bst->root);
        printf("\n");
        free(bst);
    }
}