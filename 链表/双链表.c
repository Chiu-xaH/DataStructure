#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int Status;
typedef char Elemtype;
typedef struct Node {
    Elemtype data;
    struct Node *next,*piror;
} Node,*LinkList;

Status Init(LinkList *L) {
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = *L;
    (*L)->piror = *L;
    return OK;
}

Status HeadAdd(LinkList *L,Elemtype E) {
    LinkList new,list = *L;
    new = (LinkList)malloc(sizeof(Node));
    new->data = E;
    new->next = list->next;
    // 更新原第一节点list->next的前驱指针
    list->next->piror = new;

    new->piror = list;
    list->next = new;
    return OK;
}

//删除第place位置结点
Status Delete(LinkList *L,int place) {
    int i = 1;
    LinkList list = (*L)->next;
    while (i < place && (list != *L)) {
        list = list->next;
        ++i;
    }
    if((list == *L) || i > place) {
        return ERROR;
    }
    //[list]-[new]-[]
    //[list]-[]
    //改new->next->piror
    LinkList new = list->next;
    new->next->piror = list;
    list->next = new->next; 
    free(new);
    return OK;
}


Status GetRight(LinkList L) {
    LinkList list = L->next;
    while(list != L) {
        printf("%c ",list->data);
        list = list->next;
    }
    printf("\n");
    return OK;
}

Status GetLeft(LinkList L) {
    LinkList list = L->piror;
    while(list != L) {
        printf("%c ",list->data);
        list = list->piror;
    }
    printf("\n");
    return OK;
}
/*
[]-[]-[]-
        |
        -

*/

int main() {
    Status i;
    LinkList L;
    i = Init(&L);
    i = HeadAdd(&L,'A');
    i = HeadAdd(&L,'B');
    i = HeadAdd(&L,'C');
    i = GetRight(L);
    i = GetLeft(L);
    i = Delete(&L,1);
    printf("%d\n",i);
    i = GetLeft(L);
    i = GetRight(L);

    return 0;
}