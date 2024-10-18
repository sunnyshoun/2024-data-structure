#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack{
    char data;
    struct Stack* next;
} Node;

void insert(Node** head, char data){
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

char top(Node* head){
    if(!head) return '\0';
    return head->data;
}

char pop(Node** head){
    if(!*head) return '\0';
    Node* delNode = *head;
    char returnData = delNode->data;
    *head = delNode->next;
    free(delNode);
    return returnData;
}

void printStack(Node* head){
    while(head){
        printf("%c", head->data);
        head = head->next;
    }
    printf("\n");
}

bool isOperator(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/'){
        return true;
    }
    return false;
}

int getPriority(char c){
    if(c == '+' || c == '-') return 1;
    else if(c == '*' || c == '/') return 2;
    else return 0;
}

int main(){
    Node* head = NULL;
    char c;
    while((c = getchar()) != EOF && c != '\n'){
        if(isOperator(c)){
            while(getPriority(top(head)) >= getPriority(c)){
                printf("%c", pop(&head));
            }
            insert(&head, c);
        }
        else{
            printf("%c", c);
        }
    }
    while(head){
        printf("%c", pop(&head));
    }
}