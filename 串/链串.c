#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define OK 1
#define ERROR 0
#define MAXSIZE 4

typedef int Status;
typedef char ElemType; 

typedef struct Node {
    struct Node *next;
    ElemType data[MAXSIZE];
} Node,*LinkString;

Status Init(LinkString *L) {
    *L=(LinkString)malloc(sizeof(Node));
    if(!(*L)) 
            return ERROR;
    (*L)->next = NULL;

    return OK;
}

Status HeadAdd(LinkString *L,ElemType E[MAXSIZE]) {
    LinkString new,list = *L;
    new = (LinkString)malloc(sizeof(Node));
    strcpy(new->data,E);
    new->next = list->next;
    list->next = new;
    return OK;
}

Status TailAdd(LinkString *L,ElemType E[MAXSIZE]) {
    LinkString new,list = *L;
    new = (LinkString)malloc(sizeof(Node));
    while(list->next) {
        list = list->next;
    }
    list->next = new;
    strcpy(new->data,E);
    new->next = NULL;
    return OK;
}

void Get(LinkString L) {
    LinkString str = L->next;
    while(str) {
        printf("%s",str->data);
        str = str->next;
    }
}

//S1是S2子串返回OK，不是返回ERROR
Status isSon(LinkString S1,LinkString S2) {
    int ptr1 = 0,ptr2 = 0;
    LinkString str1 = S1;
    LinkString str2 = S2;
    LinkString start2 = S2;  // 用于保存 S2 中开始匹配的节点
    while(str2) {
        if(str1->data[ptr1] == str2->data[ptr2]) {
            ptr1++;
            ptr2++;
            if(ptr1 >= MAXSIZE) {
                if(str1->next) {
                    str1 = str1->next;
                    ptr1 = 0;
                } else {
                    return OK;
                }
            }
        } else {
            ptr1 = 0;
            str1 = S1;
            ptr2++;
            if(ptr2 >= MAXSIZE) {
                start2 = start2->next;
                str2 = start2;
                ptr2 = 0;
            } else {
                str2 = start2;
            }
        }
        if(ptr2 >= MAXSIZE) {
            str2 = str2->next;
            ptr2 = 0;
        }
    }
    return ERROR;
}
//S1<S2返回-1,S1=S2返回0,S1>S2返回1
int Compare(LinkString S1,LinkString S2) {
    int ptr1 = 0,ptr2 = 0;
    LinkString str1 = S1;
    LinkString str2 = S2;
    while(str1 && str2) {
        if(str1->data[ptr1] > str2->data[ptr2]) {
            return 1;
        } else if(str1->data[ptr1] < str2->data[ptr2]) {
            return -1;
        }
        ptr1++;
        ptr2++;

        if(str1->data[ptr1] == '\0') {
            str1 = str1->next;
            ptr1 = 0;
        }
        
        if(str2->data[ptr2] == '\0') {
            str2 = str2->next;
            ptr2 = 0;
        }
        //谁先结束谁小
        if(!str1 && str2) {
            return -1;
        } else if(str1 && !str2) {
            return 1;
        }
    }
    return 0;
}

int main() {
    LinkString L,L2;
    Init(&L);
    Init(&L2);
    TailAdd(&L,"ABC");
    TailAdd(&L,"DEF");
    TailAdd(&L,"GHI");
    TailAdd(&L2,"ABC");
    //Get(L);
}
