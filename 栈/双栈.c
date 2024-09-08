//双栈共享
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 20
#define STACKONE 1
#define STACKTWO 2

/*
双栈结构示意
    栈1          栈2
[ OOO      | |         ]
 ^                   ^
 -1               MAXSIZE
*/

typedef int Status;
typedef int Elemtype;
typedef struct {
    int top1;
    int top2;
    Elemtype data[MAXSIZE];
} DoubleStack;

Status Init(DoubleStack *S) {
    S->top1 = -1;
    S->top2 = MAXSIZE;
    return OK;
}

Status isEmpty(DoubleStack S) {
    if(S.top1 + 1 == S.top2) {
        return ERROR;
    } else {
        return OK;
    }
}

Status Push(DoubleStack *S,Elemtype E,int stackNumber) {
    if(S->top1 + 1 == S->top2) {
        return ERROR;
    }
    if(stackNumber == STACKONE) {
        S->top1++;
        S->data[S->top1] = E;
        return OK;
    } else if(stackNumber == STACKTWO) {
        S->top2--;
        S->data[S->top2] = E;
        return OK;
    }
}

Status Pop(DoubleStack *S,int stackNumber) {
    if(stackNumber == STACKONE) {
        if(S->top1 == -1) {
            return ERROR;
        }
        S->top1--;
        return OK;
    }
    if(stackNumber == STACKTWO) {
        if(S->top2 == MAXSIZE) {
            return ERROR;
        }
        S->top2++;
        return OK;
    }
}

Status Get(DoubleStack *S) {
    if(S->top1 == -1 && S->top2 == MAXSIZE) {
        return ERROR;
    }

    printf("[ ");
    for(int i = 0;i <= S->top1;i++) {
        printf("%d ",S->data[i]);
    }
    printf(" || ");
    for(int i = S->top2;i < MAXSIZE;i++) {
        printf("%d ",S->data[i]);
    }
    printf("]");

    return OK;
}

int main() {
    Status i;
    DoubleStack S;
    i = Init(&S);
    i = Push(&S,1,STACKONE);
    i = Push(&S,2,STACKONE);
    i = Push(&S,3,STACKONE);
    i = Push(&S,6,STACKTWO);
    i = Push(&S,5,STACKTWO);
    i = Push(&S,4,STACKTWO);

    i = Get(&S);

    i = Pop(&S,STACKONE);
    i = Pop(&S,STACKTWO);
    i = Pop(&S,STACKTWO);

    printf("\n");
    i = Get(&S);
}