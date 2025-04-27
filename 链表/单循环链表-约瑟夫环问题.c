#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int Status;
typedef int Elemtype;
typedef struct Node {
    Elemtype data;
    struct Node *next;
} Node,*LinkList;

Status Init(LinkList *L) {
    *L=(LinkList)malloc(sizeof(Node));
    if(!(*L)) 
            return ERROR;
    (*L)->next=(*L); 
    return OK;
}


Status HeadAdd(LinkList *L,Elemtype E) {
    LinkList new,list = *L;
    new = (LinkList)malloc(sizeof(Node));
    new->data = E;
    new->next = list->next;
    list->next = new;
    return OK;
}

Status Get(LinkList L) {
    LinkList list = L->next;
    while(list != L) {
        printf("%d ",list->data);
        list = list->next;
    }
    printf("\n");
    return OK;
}

int Length(LinkList *L) {
    LinkList list = (*L)->next;
    int count = 0;
    while(list != (*L)) {
        list = list->next;
        count++;
    }
    return count;
}


/*约瑟夫环问题
约瑟夫，是一个古犹太人，曾经在一次罗马叛乱中担任将军，
后来战败，他和朋友及另外39个人躲在一口井里。
被发现后，罗马人表示只要投降就不死，
约瑟夫和朋友想投降，可是其他人坚决不同意。怎么办呢    
让41个人围成一个圆圈，从第一个人开始报数，数到3的那个人被旁边的人杀死。
这样就可以避免自杀了，因为犹太人的信仰是禁止自杀的。
约瑟夫和朋友站在什么位置才保住了性命呢？
*/
//约瑟夫算法-思想：递归
void Count(LinkList *L,int count) {
    LinkList list = (*L);
    while(list->next != (*L)) {
        LinkList old = list->next;
        if(count == 2) {
            //删除下一个结点，下一个结点继续重新数
            list->next = old->next;
            free(old);
            count = 0;
        }
        count++;
        if(list->next != (*L))
        list = list->next;
        else count--;
    }

    if(Length(L) != 2) {
       Count(L,count);
    }
}

void YueSeFu() {
    Status I;
    LinkList L;
    I = Init(&L);
    for(int i = 41;i > 0;i--) {
        I = HeadAdd(&L,i);
    }
    Count(&L,0);
    I = Get(L);
}

int main() {
    YueSeFu();
    //跟单链表区别就是循环时结束条件（碰尾条件）改成不等于头节点
  //  Status i;
   // LinkList L;
   // i = Init(&L);
   // i = HeadAdd(&L,'A');
  //  i = HeadAdd(&L,'B');
  //  i = HeadAdd(&L,'C');
   // i = HeadAdd(&L,'D');
   // printf("Length = %d\n",Length(&L));
   // i = Get(L);

}