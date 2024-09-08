#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100
#define MIN -32798

typedef int Status;
typedef int ElemType;
typedef struct {
    int front;//指向队头
    int count;
    ElemType data[MAXSIZE];
} Queue;

Status Init(Queue *Q) {
    Q->count = 0;
    Q->front = 0;
    for(int i = 0;i< MAXSIZE;i++) {
        Q->data[i] = MIN;
    }
    return OK;
}

Status Add(Queue *Q,ElemType E) {
    if(Q->count == MAXSIZE) {
        return ERROR;
    }
    int rear = Q->count+Q->front-1;
    rear++;
    rear %= MAXSIZE;
    Q->data[rear] = E;
    Q->count++;
    return OK;
}

Status DeAdd(Queue *Q) {
    if(Q->count == 0) {
        return ERROR;
    }
    Q->front++;
    Q->front %= MAXSIZE;
    Q->count--;
    return OK;
}

void Get(Queue Q) {
    for(int i = Q.front;i < Q.count;i++) {
        if(Q.data[i] != MIN) {
            printf("%d ",Q.data[i]);
        }
    }
}

int main() {
    Queue Q;
    Init(&Q);
    Add(&Q,1);
    Add(&Q,2);
    Add(&Q,3);
    Add(&Q,4);
    Add(&Q,5);
    DeAdd(&Q);
    Get(Q);
}