//如果采用带尾指针的单循环链表作为队列的存储结构，设计算法以实现队列的各运算。
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 20

typedef int Status;
typedef char ElemType;

typedef struct QueueNode {
    ElemType data;
    struct QueueNode *next;
} QueueNode,*LinkListPtr;

typedef struct {
    LinkListPtr front;
    LinkListPtr rear;
} LinkQueue;

Status Init(LinkQueue *Q) {
    LinkListPtr head = (LinkListPtr)malloc(sizeof(QueueNode));
    Q->front = head;
    Q->rear = head;
    Q->front->next = head;
    return OK;
}

Status Add(LinkQueue *Q,ElemType E) {
    LinkListPtr new = (LinkListPtr)malloc(sizeof(QueueNode));
    new->data = E;
    new->next = Q;
    Q->rear->next = new;
    Q->rear = new;
    return OK;
}

Status DeAdd(LinkQueue *Q) {
    LinkListPtr old = Q->front->next;
    Q->front->next = old->next;
    free(old);
    return OK;
}

Status Get(LinkQueue *Q) {
    LinkListPtr list = Q->front->next;
    while (list  != Q) {
        printf("%c ",list->data);
        list = list->next;
    }
    printf("\n");
    return OK;
}

int main() {
    LinkQueue Q1,Q2;
    Status i;
    i = Init(&Q1);
    i = Init(&Q2);
    i = Add(&Q1,'A');
    i = Add(&Q1,'B');
    i = Add(&Q1,'C');
   
    i = Add(&Q1,'D');
    i = Add(&Q1,'E');
    i = Add(&Q1,'F');
    i = Get(&Q1);
    i = DeAdd(&Q1);
    i = DeAdd(&Q1);
   i = Get(&Q1);
    //i = Link(&Q1,&Q2);
   // i = Get(&Q1);
   // i = Reverse(&Q1);
   // i = Get(&Q1);
    return 0;
}