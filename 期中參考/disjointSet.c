#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DisjointSetNode{
    int height;
    struct DisjointSetNode* parent;
} Node;

Node* nodeArr[10001] = {NULL};

Node* findRoot(Node* node){
    if (!node->parent) return node;
    Node* root = findRoot(node->parent);
    node->parent = root;
    return root;
}

void initialNode(int index){
    nodeArr[index] = malloc(sizeof(Node));
    nodeArr[index]->parent = NULL;
    nodeArr[index]->height = 1;
}

void unionSets(int a, int b){
    if(a == b) return;
    if(!nodeArr[a]) initialNode(a);
    if(!nodeArr[b]) initialNode(b);

    Node* a_root = findRoot(nodeArr[a]);
    Node* b_root = findRoot(nodeArr[b]);
    if(a_root != b_root){
        if(a_root->height > b_root->height){
            b_root->parent = a_root;
        }
        else{
            a_root->parent = b_root;
            if(a_root->height == b_root->height){
                (b_root->height)++;
            }
        }
    }
}

bool inSameSet(int a, int b){
    if(a == b) return true;
    if(!nodeArr[a] || !nodeArr[b]) return false;
    return findRoot(nodeArr[a]) == findRoot(nodeArr[b]);
}

int main(){
    int N, M, Q, A, B;
    scanf("%d %d %d", &N, &M, &Q);
    for(int i=0; i<M; i++){
        scanf("%d %d", &A, &B);
        unionSets(A, B);
    }
    for(int i=0; i<Q; i++){
        scanf("%d %d", &A, &B);
        if(inSameSet(A, B)){
            printf(":)\n");
        }
        else{
            printf(":(\n");
        }
    }
}