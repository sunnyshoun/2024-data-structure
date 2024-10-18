#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int minHeap[101];
int lastIndex = -1;

int leftIndex(int index){
    return 2 * index + 1;
}

int rightIndex(int index){
    return 2 * index + 2;
}

int parentIndex(int index){
    return (index - 1) / 2;
}

void swap(int index1, int index2){
    int temp = minHeap[index1];
    minHeap[index1] = minHeap[index2];
    minHeap[index2] = temp;
}

void Insert(int data){
    int curIndex = ++lastIndex;
    minHeap[curIndex] = data;
    if(curIndex == 0) return;

    while(minHeap[curIndex] < minHeap[parentIndex(curIndex)]){
        swap(curIndex, parentIndex(curIndex));
    }
}

void Delete(int target){
    int curIndex = -1;
    while(minHeap[++curIndex] != target);
    swap(curIndex, lastIndex--);
    while(true){
        int temp = minHeap[curIndex];
        if(minHeap[curIndex] < minHeap[leftIndex(curIndex)] && minHeap[curIndex] < minHeap[rightIndex(curIndex)]){
            break;
        }
        if(minHeap[curIndex] < minHeap[leftIndex(curIndex)] && minHeap[curIndex] > minHeap[rightIndex(curIndex)]){
            swap(curIndex, rightIndex(curIndex));
        }
        else if(minHeap[curIndex] > minHeap[leftIndex(curIndex)] && minHeap[curIndex] < minHeap[rightIndex(curIndex)]){
            swap(curIndex, leftIndex(curIndex));
        }
    }
}

int main(){
    char cmd[10];
    while(scanf("%s", cmd) != EOF){
        if(strcmp(cmd, "quit") == 0) break;
        int data;
        scanf("%d", &data);
        if(strcmp(cmd, "insert") == 0){
            Insert(data);
        }
        else if(strcmp(cmd, "delete") == 0){
            Delete(data);
        }
    }
    for(int i = 0; i < lastIndex + 1; i++){
        printf("%d ", minHeap[i]);
    }
}