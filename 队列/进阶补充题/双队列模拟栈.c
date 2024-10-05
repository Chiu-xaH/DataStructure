#include <stdio.h>
#include <stdlib.h>
//借助两个队列模拟栈，拔高题，备考可不做
#define OK 1
#define ERROR 0
#define MAXSIZE 100
#define QUEUE1 1
#define QUEUE2 2

typedef int Status;
typedef int Elemtype;

//队列
typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
} Queue;

void InitQueue(Queue *Q) {
    Q->front = 0;
    Q->rear = 0;
}

void Add(Queue *Q,Elemtype E) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return;
    }	
	Q->data[Q->rear] = E;	
    Q->rear++;		
	Q->rear = Q->rear % MAXSIZE;
}

void DeAdd(Queue *Q,Elemtype *E) {
    if(Q->front == Q->rear) {
        return;
    }
    *E = Q->data[Q->front];
    Q->front++;
    Q->front = Q->front % MAXSIZE;
}

int Length(Queue Q) {
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

Status GetQueue(Queue Q) {
    if(Q.front == Q.rear) {
        return ERROR;
    }
    int i = Q.front;
    while(i != Q.rear) {
        printf("%d ",Q.data[i]);
        i++;
        i = i % MAXSIZE;
    }
    printf("\n");
    return OK;
}

Status isFull(Queue Q) {
    if((Q.rear+1)%MAXSIZE == Q.front) {
        return OK;
    } else {
        return ERROR;
    }
}

typedef struct {
    Queue Q1,Q2;
    int mainContainer; //主容器 =QUEUE1代表主容器为Q1,=QUEUE2代表Q2
    //主容器用来入栈，副容器默认为空，用于辅助出栈
    //入栈时直接入队主容器
    //出栈时将主容器前面元素悉数移动到副容器，最后出队主容器剩余的一个元素就是出栈元素，此时主容器为空，调换mainContainer值，将已经空的原主容器设为副容器，此时出栈成功且状态调整完成
} Stack;

void InitStack(Stack *S) {
    InitQueue(&S->Q1);
    InitQueue(&S->Q2);
    S->mainContainer = QUEUE1;
}

void SwapMainContainer(Stack *S) {
    if(S->mainContainer == QUEUE1) 
        S->mainContainer = QUEUE2;
    else
        S->mainContainer = QUEUE1;
}

void Push(Stack *S,Elemtype data) {
    Queue *Q;
    if(S->mainContainer == QUEUE1) {
        Q = &S->Q1;
    } else {
        Q = &S->Q2;
    }
    Add(Q,data);
}

Status Pop(Stack *S,Elemtype *data) {
    Queue *Q,*otherQ;
    if(S->mainContainer == QUEUE1) {
        Q = &S->Q1;
        otherQ = &S->Q2;
    } else {
        Q = &S->Q2;
        otherQ = &S->Q1;
    }
    while(Length(*Q) != 1) {
        Elemtype E;
        DeAdd(Q,&E);
        Add(otherQ,E);
    }
    DeAdd(Q,data);
    if(Length(*Q) != 0) {
        return ERROR;
    }
    SwapMainContainer(S);
    return OK;
}

Status isEmptyStack(Stack S) {
    Queue *Q;
    if(S.mainContainer == QUEUE1) {
        Q = &S.Q1;
    } else {
        Q = &S.Q2;
    }
    if(Length(*Q) == 0) {
        return OK;
    } else {
        return ERROR;
    }
}

Elemtype GetTop(Stack S) {
    Queue *Q;
    if(S.mainContainer == QUEUE1) {
        Q = &S.Q1;
    } else {
        Q = &S.Q2;
    }
    if(isEmptyStack(S)) {
        return -1;
    }
    int ptr = Q->rear-1;
    return Q->data[ptr];
}

void GetStack(Stack S) {
    Queue *Q;
    if(S.mainContainer == QUEUE1) {
        Q = &S.Q1;
    } else {
        Q = &S.Q2;
    }
    printf("[ ");
    GetQueue(*Q);
}

void Free(Stack *S) {
    free(S);
}
//继续拔高：用一个队列可以模拟栈吗？如果能的话设计一下？
int main() {
    Stack S;
    InitStack(&S);
    Push(&S,1);
    Push(&S,2);
    Push(&S,3);
    Push(&S,4);
    Elemtype E;
    Pop(&S,&E);
    Pop(&S,&E);
    GetStack(S);
    Elemtype top = GetTop(S);
    printf("TOP IS %d",top);
}