#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QueueNode{
    int data;
    struct QueueNode* next;
} Node;

typedef struct Queue{
    Node* front;
    Node* rear;
} Queue;

Queue* newQueue(){
    Queue* queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, int data){
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if(!queue->rear){
        queue->front = newNode;
        queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

int dequeue(Queue* queue){
    if(!queue->front) return 0;

    Node* delNode = queue->front;
    int data = delNode->data;
    if(delNode == queue->rear){
        queue->front = NULL;
        queue->rear = NULL;
    }
    else{
        queue->front = delNode->next;
    }
    free(delNode);
    return data;
}

bool isEmpty(Queue* queue){
    if(queue->front) return false;
    return true;
}

void printQueue(Queue* queue){
    Node* curNode = queue->front;
    while(curNode){
        printf("%d->", curNode->data);
        curNode = curNode->next;
    }
    printf("NULL\n");
}

bool visited[10001] = {0};
bool connect[100][100];
int n;

int main(){
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &connect[i][j]);
        }
    }

    Queue* queue = newQueue();
    enqueue(queue, 0);
    visited[0] = true;
    while(!isEmpty(queue)){
        int walk = dequeue(queue);
        printf("%d ", walk+1);

        for(int i=0; i<n; i++){
            if(connect[walk][i] && !visited[i]){
                visited[i] = true;
                enqueue(queue, i);
            }
        }
    }
}