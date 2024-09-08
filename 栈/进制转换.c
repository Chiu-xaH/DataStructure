#include <stdio.h>

#define MAXSIZE 20
#define OK 1
#define ERROR 0

#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15


typedef int Status;
typedef int Elemtype;
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
        printf("%d ",S.data[i]);
    }
    printf("]\n");
    return OK;
}

Status AllPop(Stack *S) {
    if(S->top == -1) {
        return ERROR;
    }

    for(int i = S->top;i > -1;i--) {
        Elemtype E;
        Pop(S,&E);
        printf("%d ",E);
    }
    printf("\n");
    return OK;
}


//十进制转化为二进制输出
void Transfer(int num) {
    Stack S;
    InitStack(&S);
    while(num > 0) {
        int yuShu = num % 2;
        num /= 2;
        Push(&S,yuShu);
    }
    AllPop(&S);
}

//以此类推，容易实现HEX(16),DEC(10),BIN(2),O(8)互相转换

int main() {
    Transfer(9);
}
