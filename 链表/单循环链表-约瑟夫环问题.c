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
//约瑟夫算法-思想：
void Count(LinkList *L, int k, int m, int count) {
    LinkList list = (*L);
    while (list->next != (*L)) {
        LinkList old = list->next;
        if (count == k - 1) { // 第k个出圈
            list->next = old->next;
            free(old);
            count = 0;
        } else {
            count++;
            if (list->next != (*L)) {
                list = list->next;
            } else {
                count--; // 如果下一个是头节点，不移动且不加count
            }
        }
    }

    // 如果剩余人数 > m，继续递归
    if (Length(L) > m) {
        Count(L, k, m, count);
    }
}
//总共n个人，从1开始顺序编号，排成一个圆形队列。从1号开始报数，报数到k的人出圈。然后从出圈位置的下一个人继续从1报数，到k的人出圈。已经出圈的人不再参与报数，继续上面的做法，直到环形队列中最后只留下m个人。
//递归 n为初始总人数；k为出圈的报数；m为最后留下的人数。
void YueSeFu(int n, int k, int m) {
    Status I;
    LinkList L;
    I = Init(&L); // 初始化循环链表
    for (int i = n; i > 0; i--) {
        I = HeadAdd(&L, i); // 从大到小头插法
    }
    Count(&L, k, m, 0); // 启动递归，初始count为0
    I = Get(L); // 输出/处理最后剩下的m个结点
}

int main() {
    YueSeFu(41,3,2); // 41个人，报数到3的人出圈，最后留下2个人
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