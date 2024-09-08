#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 20

typedef int Status;
typedef char ElemType;
//节点
typedef struct StackNode {
    ElemType data;
    struct StackNode *next;
}StackNode,*LinkStackPtr;
//
typedef struct {
    LinkStackPtr top;
    int count;
} LinkStack;

Status Init(LinkStack *S) {
    S->top = (LinkStackPtr)malloc(sizeof(StackNode));
    S->top = NULL;
    S->count = 0;
    return OK;
}

Status Push(LinkStack *S,ElemType E) {
    LinkStackPtr new = (LinkStackPtr)malloc(sizeof(StackNode));
    new->data = E;
    new->next = S->top;
    S->top = new;
    S->count++;
    return OK;
}

Status Pop(LinkStack *S,ElemType *E) {
    LinkStackPtr link;
    link = S->top;
    *E = link->data;
    S->top = S->top->next;
    free(link);
    S->count--;
    return OK;
}

Status Get(LinkStack *S) {
    LinkStackPtr link = S->top;
    while(link) {
        printf("%d ",link->data);
        link = link->next;
    }
    printf("]\n");
    return OK;
}


///回文序列判断
void Huiwen(char str[]) {
    Status status;
    LinkStack S;
    status = Init(&S);
    int i = 0;
    while(str[i] != '\0') {
        status = Push(&S,str[i]);
        i++;
    }
    char newStr[MAXSIZE];
    int j = 0;
    LinkStackPtr link = S.top;
    while(link) {
        newStr[j] = link->data;
        j++;
        link = link->next;
    }
    newStr[j] = '\0';

    if(!strcmp(newStr,str)) {
        printf("Yes");
    } else printf("No");
}



int main() {
   // Status i;
  //  ElemType E;
  //  LinkStack S;
  //  i = Init(&S);
    //i = Push(&S,'1');
   // i = Push(&S,'2');
  //  i = Push(&S,'3');
   // i = Pop(&S,&E);
   // i = Get(&S);
   char str[MAXSIZE];
   printf("Please Input char\n");
   gets(str);
   Huiwen(str);
    return 0;
}