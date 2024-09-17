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
    *L=(LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
    if(!(*L)) /* 存储分配失败 */
            return ERROR;
    (*L)->next=NULL; /* 指针域为空 */

    return OK;
}
//在第place位置之前插入
Status Insert(LinkList *L,Elemtype E,int place) {
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
//元素递增有序，设计算法在顺序表中插入元素x，
//要求插入后仍保持其递增有序特性，并要求时间尽可能少。
Status Question1(LinkList *L,Elemtype E) {
    int place = 0;
    LinkList list = (*L)->next;
    int old  = list->data;
    // 4 2 1
    while(old > E) {
      //  printf("%d  ",list->data);
        old = list->next->data;
        place++;
        list = list->next;
        
    }
   // printf("%d",place);
    return Insert(L,E,place);
}

int Length(LinkList *L) {
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
    int count = 0;
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
//                 [pre]-[list]
//[head]  [A]<-[B]<-[C]   NULL
//[head]<-[A]<-[B]<-[C]<-[head]

Status ReverseUpdate(LinkList *L) {
    //从第1、2元素开始，最后处理头结点
    LinkList list = (*L)->next->next,pre = (*L)->next,head = *L;
    //只有一个元素加头结点，没必要逆置
    if(list == NULL) {
        return OK;
    }
    pre->next = NULL;
    while(list) {
        //暂存初始状态下一个节点
        LinkList nexts = list->next;
        list->next = pre;
        pre = list;
        list = nexts;
    }
    //处理头节点
    head->next = pre;
    return OK;
}

Status Get(LinkList L) {
    LinkList list = L->next;
    while(list) {
        printf("%d ",list->data);
        list = list->next;
    }
    printf("\n");
    return OK;
}
//L1复制到L2（L2为刚初始化的空表）
Status Copy(LinkList *L1,LinkList *L2) {
    LinkList list = (*L1)->next,newList = (*L2);
    while (list) {
        LinkList new = (LinkList)malloc(sizeof(Node));
        new->data = list->data;
        new->next = NULL;

        newList->next = new; // 将新节点连接到L2的尾部
        newList = new; // 更新L2的尾节点

        list = list->next;
    }
    return OK;
}
//将L1拼接到L2
Status Link(LinkList *L1,LinkList *L2) {
    LinkList list1 = (*L1)->next,list2 = (*L2);

    while(list2->next) {
            list2 = list2->next;
    }
    
    while(list1) {
        LinkList new = (LinkList)malloc(sizeof(Node));
        new->data = list1->data;
        new->next = NULL;
        

        list2->next = new;
        list2 = list2->next;
        list1 = list1->next;
    }
    return OK;
}
//传入两个递增有序链表，求并集
//L1{1,2,3,4,5}
//L2{0,2,4,6,8}
//重复直到其中一个指针超出数组范围，最后将剩余的元素直接加入并集中。*/
Status LinkSet(LinkList *L1,LinkList *L2) {
    LinkList ptr1 = (*L1)->next,ptr2 = (*L2)->next,old = *L1;
    while(ptr1 != NULL && ptr2 != NULL) {
        if(ptr1->data < ptr2->data) {
            old = ptr1;
            ptr1 = ptr1->next;
        } else if(ptr1->data > ptr2->data) {
            //ptr2插入到ptr1前面，并移动指针
            //[old]-[ptr1]-[ptr1->next] 
            //[old]-[ptr2]-[ptr1]-[ptr1->next] 
            LinkList new = (LinkList)malloc(sizeof(Node));
            new->data = ptr2->data;
            new->next = ptr1;
            old->next = new;
            ptr2 = ptr2->next;
        } else {
            //保留元素，同时移动指针
            old = ptr1;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    while(ptr2 != NULL) {
        TailAdd(L1,ptr2->data);
        ptr2 = ptr2->next;
    }
}
//传入两个递增有序链表，求交集
void JointSet(LinkList *L1,LinkList *L2) {
    LinkList ptrL1 = (*L1)->next,ptrL2 = (*L2)->next;
    LinkList oldL1 = (*L1);
    while(ptrL1 != NULL && ptrL2 != NULL) {
        if(ptrL1->data < ptrL2->data) {
            //删除结点
            oldL1->next = ptrL1->next;
            free(ptrL1);
            ptrL1 = oldL1->next;
        } else if(ptrL1->data > ptrL2->data) {
            ptrL2 = ptrL2->next;
        } else {
            oldL1 = ptrL1;
            ptrL1 = ptrL1->next;
            ptrL2 = ptrL2->next;
        }
    }
    while(ptrL1 != NULL) {
        oldL1->next = ptrL1->next;
        free(ptrL1);
        ptrL1 = oldL1->next;
    }
}
//传入两个递增有序链表，判断L2是否为L1子集
Status SubSet(LinkList *L1,LinkList *L2) {
    LinkList ptr1 = (*L1)->next,ptr2 = (*L2)->next;
    while(ptr2 != NULL && ptr1 != NULL) {
        if(ptr2->data > ptr1->data) {
            ptr1 = ptr1->next;
        } else if(ptr2->data < ptr1->data) {
            return ERROR;
        } else {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    //L2是否有剩余未匹配，有则不是子集
    if(ptr2 != NULL) {
        return ERROR;
    } else {
        return OK;
    }
}
//转换为单循环链表
void Transfer(LinkList *L) {
    if (*L == NULL) {
        return; // 如果链表为空，则直接返回
    }
    LinkList list = *L;
    while(list->next) {
        list = list->next;
    }
    list->next = *L;
}
//C=A交B 链表并非递增有序
LinkList JointSetUpdate(LinkList L1,LinkList L2) {
    LinkList list;
    Init(&list);
    LinkList list1 = L1->next;
    while(list1) {
        LinkList list2 = L2->next;
        while(list2) {
            if(list2->data == list1->data) {
                TailAdd(&list,list2->data);
            }
            list2 = list2->next;
        }
        list1 = list1->next;
    }
    return list;
}
//C=A交B 递增有序 略
//A=A交B 递增有序
//A={2,3,4,5}
//B={0,2,4,6}
//A={2,4}
void LinkSetUpdate(LinkList *L1,LinkList L2) {
    LinkList list1 = (*L1)->next,list2 = L2->next,prv = *L1;
    while(list1 && list2) {
        if(list1->data > list2->data) {
            list2 = list2->next;
        } else if(list1->data < list2->data) {
            prv->next = list1->next;
            free(list1);
            list1 = prv->next;
        } else {
            prv = list1;
            list1 = list1->next;
            list2 = list2->next;
        }
    }
    while (list1) {
        //prv->list1->list1next
        prv->next = list1->next;
        free(list1);
        list1 = prv->next;
    }
}
//A=A并B 递增有序 略
//C=A并B 递增有序
//A={1,2,3,4,5}
//B={0,2,4,6}
//C={1,2,3,4,5,0,6}
LinkList LinkSet2(LinkList L1,LinkList L2) {
    LinkList L;
    Init(&L);
    LinkList list1 = L1->next,list2 = L2->next;
    while(list1) {
        TailAdd(&L,list1->data);
        list1 = list1->next;
    }
    list1 = L1->next;
    while(list1 && list2) {
        if(list1->data > list2->data) {
            TailAdd(&L,list2->data);
            list2 = list2->next;
        } else if(list1->data < list2->data) {
            list1 = list1->next;
        } else {
            list1 = list1->next;
            list2 = list2->next;
        }
    }
    while(list2) {
        TailAdd(&L,list2->data);
        list2 = list2->next;
    }
}
//设计算法两个递增有序的链表合并为一个递增有序的链表，要求时间复杂度为两个表长之和的数量级
//A={0,1,2,3,4,5}
//B={0,2,4,6}
//C={0,1,2,3,4,5,6}
void MergeUp(LinkList *L1,LinkList L2) {
    LinkList list1 = (*L1)->next,list2 = L2->next;
    while(list1 && list2) {
        if(list1->data > list2->data) {
            HeadAdd(L1,list2->data);
            list2 = list2->next;
        } else if(list1->data < list2->data) {
            list1 = list1->next;
        } else {
            list1 = list1->next;
            list2 = list2->next;
        }
    }
    while(list2) {
        TailAdd(L1,list2->data);
        list2 = list2->next;
    }
}
//设计算法两个递增有序的链表合并为一个递减有序的链表，要求时间复杂度为两个表长之和的数量级
//A={1,2,3,4,5}
//B={0,2,4,6}
//C={6,5,4,3,2,1,0}
void MergeDown(LinkList *L1,LinkList L2) {
    MergeUp(L1,L2);
    ReverseUpdate(L1);
}
//设计算法分解链表为奇数链表、偶数链表
void Resolve(LinkList L,LinkList *JiL,LinkList *OuL) {
    LinkList list = L->next;
    Init(JiL);
    Init(OuL);
    while(list) {
        if(list->data % 2 == 0) {
            TailAdd(OuL,list->data);
        } else {
            TailAdd(JiL,list->data);
        }
        list = list->next;
    }
}

//补充题：递增有序链表，设计算法去重，要求尽可能的高效率
//思路：用两个指针从头扫描，遇到相同的第一个指针固定，第二个继续直到不相同，然后删除中间重复的若干节点即可，补充这道题时我已经考完了，具体实现欢迎补充
void DeWeight() {}

int main() {
    Status i;
    LinkList L,newL,L2;
    i = Init(&L);
    i = Init(&newL);
    i = Init(&L2);
  //  i = HeadAdd(&L,'D');
  //  i = HeadAdd(&L,'B');
  //  i = HeadAdd(&L,'A');

    i = HeadAdd(&L,5);
    i = HeadAdd(&L,4);
    i = HeadAdd(&L,3);
    i = HeadAdd(&L,2);
    i = HeadAdd(&L,1);
    

    i = HeadAdd(&L2,6);
    i = HeadAdd(&L2,4);
    i = HeadAdd(&L2,2);
    i = HeadAdd(&L2,0);
 
   // i = Insert(&L,'C',2);
  //  i = Delete(&L,4);
  //  i = Reverse(&L);
  //  i = Copy(&L,&newL);
 // printf("%d",Length(&L));
   // i = Get(L);
   // i = Get(L);
    //i = Question1(&L2,3);
    //i = Get(L2);
    //LinkSet(&L,&L2);
    //JointSet(&L,&L2);
    ///i = Get(L);
   // i = SubSet(&L,&L2);
    //printf("is %d",i);
    //LinkSetUpdate(&L,L2);
    //Get(L);
   // LinkSet2(L,L2);
   //MergeUp(&L,L2);
  // LinkList list = MergeDown(L,L2);
   //Get(list);
   //LinkList list = JointSetUpdate(L,L2);
   //Get(list);
   //MergeDown(&L,L2);
   //Get(L);
   // i = Link(&L,&L2);
  //  i = DeWeight(&L);
  //  i = Get(L2);
  //  i = DeWeight(&L);
   // i = Get(L2);
   LinkList JiL,OuL;
   Resolve(L,&JiL,&OuL);
   Get(JiL);
   Get(OuL);
    return 0;
}