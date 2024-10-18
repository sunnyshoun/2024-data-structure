#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct StackNode{
    char data;
    struct StackNode* next;
} Node;

typedef struct Stack{
    Node* top;
} Stack;

Stack* newStack(){
    Stack* stack = malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

bool isEmpty(Stack* stack){
    return stack->top == NULL;
}

void insert(Stack* stack, char data){
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

char pop(Stack* stack){
    if(isEmpty(stack)) return '\0';
    Node* delNode = stack->top;
    char returnData = delNode->data;
    stack->top = delNode->next;
    free(delNode);
    return returnData;
}

void printStack(Stack* stack){
    Node* curNode = stack->top;
    while(curNode){
        printf("%c->", curNode->data);
        curNode = curNode->next;
    }
    printf("NULL\n");
}

bool isOperator(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/'){
        return true;
    }
    return false;
}

int main(){
    Stack* stack = newStack();
    char c;
    while((c = getchar()) != EOF && c != '\n'){
        if(isOperator(c)){
            insert(stack, c);
        }
        else{
            printf("%c", c);
            char popc = pop(stack);
            if(popc != '\0') printf("%c", popc);
        }
    }
}