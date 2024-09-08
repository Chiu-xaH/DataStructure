#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int Status;
typedef int ElemType;
typedef struct Node {
    struct Node *next,*prior;
    ElemType data;
} Node,*LinkList;

Status Init(LinkList *L) {
    *L = (LinkList)malloc(sizeof(Node));
    if((*L) == NULL) {
        return ERROR;
    } else {
        (*L)->next = *L;
        (*L)->prior = *L;
        return OK;
    }
}

Status HeadAdd(LinkList *L,ElemType E) {
    LinkList newNode = (LinkList)malloc(sizeof(Node));
    newNode->data = E;
    //[head]<->[list]
    //[head]<->[new]<->[list]
    LinkList list = (*L)->next;
    newNode->next = list;
    (*L)->next = newNode;
    newNode->prior = *L;
    list->prior = newNode;
    return OK;
}

Status TailAdd(LinkList *L,ElemType E) {
    LinkList newNode = (LinkList)malloc(sizeof(Node));
    newNode->data = E;
    //[list]<->[head]
    //[list]<->[new]<->[head]
    LinkList list = (*L)->prior;
    newNode->prior = list;
    (*L)->prior = newNode;
    newNode->next = *L;
    list->next = newNode;
    return OK;
}

void GetRight(LinkList L) {
    LinkList list = L->next;
    while(list != L) {
        printf("%d ",list->data);
        list = list->next;
    }
    printf("\n");
}

void GetLeft(LinkList L) {
    LinkList list = L->prior;
    while(list != L) {
        printf("%d ",list->data);
        list = list->prior;
    }
    printf("\n");
}

Status TailDelete(LinkList *L) {
    //[list]<->[old]<->[head]
    //[list]<->[head]
    LinkList old = (*L)->prior;
    LinkList list = old->prior;
    list->next = *L;
    (*L)->prior = list;
    free(old);
    return OK;
}

Status HeadDelete(LinkList *L) {
    //[head]<->[old]<->[list]
    //[head]<->[list]
    LinkList old = (*L)->next;
    LinkList list = old->next;
    list->prior = *L;
    (*L)->next = list;
    free(old);
    return OK;
}

int Length(LinkList L) {
    int count = 0;
    LinkList list = L->next;
    while(list != L) {
        count++;
        list = list->next;
    }
    return count;
}

//判断是否对称，即无论前->后还是后->前输出相同
//[HEAD]-[A]-[B]-[C]-[B]-[A]
Status isSymmetrical(LinkList L) {
    LinkList left = L->prior,right = L->next;
    while(left != right) {
        if(left->data != right->data) {
            return ERROR;
        }
        left = left->prior;
        right = right->next;
    }
    return OK;
}
//就地逆置
void Reverse(LinkList *L) {
    //[head]<->[A]<->[B]<->[C]
    LinkList left = (*L)->prior,right = (*L)->next;
    LinkList temp;
    while(right != (*L)) {
        temp = right->next;
        right->next = right->prior;
        right->prior = temp;
        right = temp;
    }
    //头节点处理
    temp = (*L)->next;
    (*L)->next = (*L)->prior;
    (*L)->prior = temp;
}

int main() {
    LinkList L;
    Init(&L);
    TailAdd(&L,1);
    TailAdd(&L,2);
    TailAdd(&L,3);
    TailAdd(&L,4);
    TailAdd(&L,5);
    //HeadAdd(&L,0);
    //HeadDelete(&L);
    //TailDelete(&L);
    GetRight(L);
    GetLeft(L);
    //Status i = isSymmetrical(L);
    //if(i) printf("YES");
    //else printf("NO");
    Reverse(&L);
    GetRight(L);
    GetLeft(L);
    return 0;
}