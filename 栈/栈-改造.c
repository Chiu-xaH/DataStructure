#include <stdio.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int Status;
typedef int ElemType;
typedef struct {
    int count;
    ElemType data[MAXSIZE];
} Stack;

Status Init(Stack *S) {
    S->count = 0;
    return OK;
}

Status Push(Stack *S,ElemType E) {
    if(S->count == MAXSIZE) {
        return ERROR;
    }
    S->data[S->count] = E;
    S->count++;
    return OK;
}

Status Pop(Stack *S) {
    if(S->count == 0) {
        return ERROR;
    }
    S->count--;
    return OK;
}

void Get(Stack S) {
    for(int i = S.count-1;i >= 0;i--) {
        printf("%d ",S.data[i]);
    }
    printf("]\n");
}

int main() {
    Stack S;
    Init(&S);
    Push(&S,1);
    Push(&S,2);
    Push(&S,3);
    Pop(&S);
    Get(S);
}