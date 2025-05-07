#include <stdio.h>

#define MAXSIZE 20
#define OK 1
#define ERROR 0

typedef int Status;
typedef char Elemtype;
typedef struct {
    int top;
    Elemtype data[MAXSIZE];
} Stack;


Status InitStack(Stack *S) {
    S->top = -1;
    return OK;
}
Status Push(Stack *S,Elemtype E) {
    if(S->top == MAXSIZE) {
        return ERROR;
    }
    S->top++;
    S->data[S->top] = E;
    return OK;
}

Status Pop(Stack *S,Elemtype *E) {
    if(S->top == -1) {
        return ERROR;
    }
    *E = S->data[S->top];
    S->top--;
    return OK;
}

Status GetStack(Stack S) {
    if(S.top == -1) {
        return ERROR;
    }

    for(int i = S.top;i > -1;i--) {
        printf("%c ",S.data[i]);
    }
    printf("]\n");
    return OK;
}

Status Length(Stack S) {
    return S.top + 1;
}

Status AllPop(Stack *S) {
    if(S->top == -1) {
        return ERROR;
    }

    for(int i = S->top;i > -1;i--) {
        Elemtype E;
        Pop(S,&E);
        printf("%c ",E);
    }
    printf("]\n");
    return OK;
}

