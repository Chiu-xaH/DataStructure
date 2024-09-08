#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 20

typedef int Status;
typedef int ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    int front,rear;
} SqQueue;

Status Init(SqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}
//通用公式
int Length(SqQueue Q) {
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}
//队列满-通用
Status isFull(SqQueue Q) {
    if((Q.rear+1)%MAXSIZE == Q.front) {
        return OK;
    } else {
        return ERROR;
    }
}
//队列空
Status isEmpty(SqQueue Q) {
    if(Q.front == Q.rear) {
        return OK;
    } else {
        return ERROR;
    }
}


Status Add(SqQueue *Q,ElemType E) {
    if(isFull(*Q)) {
        return ERROR;
    }
    Q->data[Q->rear] = E;
    Q->rear++;
    Q->rear %= MAXSIZE;
    return OK;
}

Status DeAdd(SqQueue *Q) {
    if(isEmpty(*Q)) {
        return ERROR;
    }
    Q->front++;
    Q->front %= MAXSIZE;
    return OK;
}

Status Get(SqQueue Q) {
    int i = Q.front;
    while(i != Q.rear) {
        printf("%d ",Q.data[i]);
        i++;
    }
}

int main() {
    SqQueue Q;
    Init(&Q);
    Add(&Q,1);
    Add(&Q,2);
    Add(&Q,3);
    Add(&Q,4);
    DeAdd(&Q);
    Get(Q);
}