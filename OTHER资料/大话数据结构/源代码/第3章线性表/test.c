#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int ElemType;


typedef struct {
    ElemType data;
    int cur;
} Component,StaticLinkList[MAXSIZE];

//初始化
Status InitList(StaticLinkList space) {
    int i;
    for(i = 0;i < MAXSIZE - 1;i++) {
        space[i].cur = i + 1;
    }
    space[MAXSIZE - 1].cur = 0;
    return OK;
}

int Malloc_SSL(StaticLinkList space) {
    int i = space[0].cur;
    if(space[0].cur) {
        space[0].cur = space[i].cur;
    }
    return i;
}

//长度
int ListLength(StaticLinkList L)
{
    int j=0;
    int i=L[MAXSIZE-1].cur;
    while(i)
    {
        i=L[i].cur;
        j++;
    }
    return j;
}

//插入元素
Status ListInsert(StaticLinkList list,int i,ElemType e) {
    int j,k,l;
    k = MAXSIZE - 1;
    if(i < 1 || i > ListLength(list) + 1) {
        return ERROR;
    }
    j = Malloc_SSL(list);
    if(j) {
        list[j].data = e;
        for(l = 1;l <= i -1;l++) {
            k = list[k].cur;
        }
        list[j].cur = list[k].cur;
        list[k].cur = j;
    }
    return ERROR;
}

int main() {
    StaticLinkList list;
    InitList(list);
    printf("Init Successfully");

}