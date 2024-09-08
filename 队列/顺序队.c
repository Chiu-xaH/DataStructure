#include <stdio.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 10

typedef int Status;
typedef int Elemtype;
typedef struct {
    Elemtype data[MAXSIZE];
    int front;
    int rear;
} Queue;

Status Init(Queue *Q) {
    Q->front = 0;////<--
    Q->rear = 0;//////-->
    return OK;
}

Status Add(Queue *Q,Elemtype E) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return ERROR;
    }	
	Q->data[Q->rear] = E;	
    Q->rear++;		
	Q->rear = Q->rear % MAXSIZE;
    return OK;
}

Status DeAdd(Queue *Q) {
    if(Q->front == Q->rear) {
        return ERROR;
    }
    Q->front++;
    Q->front = Q->front % MAXSIZE;
    return OK;
}

Status Get(Queue *Q) {
    if(Q->front == Q->rear) {
        return ERROR;
    }
    int i = Q->front;
    while(i != Q->rear) {
        printf("%d ",Q->data[i]);
        i++;
        i = i % MAXSIZE;
    }
    printf("\n");
    return OK;
}

int main() {
    Status i;
    Queue Q;
    i = Init(&Q);
    i = Add(&Q,1);
    i = Add(&Q,2);
    i = Add(&Q,3);
    i = Add(&Q,4);
    i = Add(&Q,5);
    i = Add(&Q,6);


    i = Get(&Q);
    i = DeAdd(&Q);
    i = DeAdd(&Q);
    i = DeAdd(&Q);
    i = DeAdd(&Q);

    i = Get(&Q);
    return 0;
}