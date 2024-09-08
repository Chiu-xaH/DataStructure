#include <stdlib.h>
#include <stdio.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int Status;
typedef int Elemtype;
typedef struct Node {
    Elemtype data;
    struct Node *next;
} Node;
typedef struct Node *LinkList;

Status InitLinkList(LinkList *L) {
    *L=(LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
    if(!(*L)) /* 存储分配失败 */
            return ERROR;
    (*L)->next=NULL; /* 指针域为空 */

    return OK;
}

//在第place位置之前插入
Status InsertLinkList(LinkList *L,Elemtype E,int place) {
    int i = 0;
    LinkList list = *L;
    while(i < place && list) {
        list = list->next;
        ++i;
    }
    if(!list || i > place) {
        return ERROR;
    }

    LinkList new = (LinkList)malloc(sizeof(Node));
    new->data = E;
    new->next = list->next;
    list->next = new;
    return OK;
}

//删除第place位置结点
Status Delete(LinkList *L,int place) {
    int i = 1;
    LinkList list = *L;
    while (i < place && (list->next)) {
        list = list->next;
        ++i;
    }
    if(!(list->next) || i > place) {
        return ERROR;
    }
    //[list]-[new]-[]
    //[list]-[]
    LinkList new = list->next;
    list->next = new->next; 
    free(new);
    return OK;
}

//头插法
Status HeadAdd(LinkList *L,Elemtype E) {
    LinkList new,list = *L;
    new = (LinkList)malloc(sizeof(Node));
    new->data = E;
    new->next = list->next;
    list->next = new;
    return OK;
}

//尾插法
Status TailAdd(LinkList *L,Elemtype E) {
    LinkList new = (LinkList)malloc(sizeof(Node));
    LinkList list = (*L);
    while(list->next != NULL) {
        list = list->next;
    }
    new->data = E;
    new->next = NULL;
    list->next = new;
    return OK;
}

int LengthLinkList(LinkList *L) {
    LinkList list = (*L)->next;
    int count = 0;
    while(list) {
        list = list->next;
        count++;
    }
    return count;
}

//逆置
//                 l1    l2
//                      old1 old2
//NULL<-[A]<-[B]<-[C]   [D]->NULL
Status Reverse(LinkList *L) {
    LinkList list2 = (*L)->next;
    LinkList list1 = NULL;
    while (list2 != NULL) {
        LinkList listOld2 = list2->next;
        LinkList listOld1 = list2;
         //逆置
        list2->next = list1;

        //右移指针
        list1 = listOld1;
        list2 = listOld2;
    }
    (*L)->next = list1;
    return OK;
}

Status GetLinkList(LinkList L) {
    LinkList list = L->next;
    while(list) {
        printf("%d ",list->data);
        list = list->next;
    }
    printf("\n");
    return OK;
}