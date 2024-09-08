//栈
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 20

typedef int Status;
typedef int Elemtype;
typedef struct {
    int top;
    Elemtype data[MAXSIZE];
} Stack;

Status Init(Stack *S) {
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

Status Pop(Stack *S) {
    if(S->top == -1) {
        return ERROR;
    }
    S->top--;
    return OK;
}

Status Get(Stack *S) {
    if(S->top == -1) {
        return ERROR;
    }
   
    for(int i = S->top;i > -1;i--) {
        printf("%d ",S->data[i]);
    }
    printf("]");
    return OK;
}

int main() {
    Status i;
    Elemtype e = 9;
    Stack *s;
    i = Init(s);
 //   printf("%d",i);
    i = Push(s,1);
    i = Push(s,2);
    i = Push(s,3);
    i = Pop(s);
    i = Pop(s);
    
  //  i = Push(s,4);
   // i = Push(s,5);
   // printf("%d",i);
    i = Get(s);
   // printf("%d",i);
}