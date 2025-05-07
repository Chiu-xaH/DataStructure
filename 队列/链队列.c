#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 20

typedef int Status;
typedef int ElemType;

typedef struct QueueNode {
    ElemType data;
    struct QueueNode *next;
} QueueNode,*LinkListPtr;

typedef struct {
    LinkListPtr front;
    LinkListPtr rear;
} LinkQueue;

Status Init(LinkQueue *Q) {
    LinkListPtr head = (LinkListPtr)malloc(sizeof(QueueNode));
    Q->front = head;
    Q->rear = head;
    Q->front->next = NULL;
    return OK;
}

Status Add(LinkQueue *Q,ElemType E) {
    LinkListPtr new = (LinkListPtr)malloc(sizeof(QueueNode));
    new->data = E;
    new->next = NULL;
    Q->rear->next = new;
    Q->rear = new;
    return OK;
}

Status DeAdd(LinkQueue *Q,ElemType *E) {
    LinkListPtr old = Q->front->next;
    *E = old->data;
    Q->front->next = old->next;
    if(Q->rear == old)		/* 若队头就是队尾，则删除后将rear指向头结点，见图中③ */
		Q->rear=Q->front;
    free(old);
    return OK;
}

Status Get(LinkQueue *Q) {
    LinkListPtr list = Q->front->next;
    while (list) {
        printf("%d ",list->data);
        list = list->next;
    }
    printf("\n");
    return OK;
}
//将Q2接到Q1后
Status Link(LinkQueue *Q1,LinkQueue *Q2) {
    Q1->rear->next = Q2->front->next;
    LinkListPtr list = Q2->front;
    while (list) {
        list = list->next;
    }
    Q1->rear = list;
    return OK;
}
//跟链表反转一样，我懒得写了，AI了
Status Reverse(LinkQueue *Q) {
   if (Q->front == Q->rear || Q->front->next == NULL) {
        return OK; // 队列为空或只有一个元素时无需反转
    }

    // 初始化三个指针：prev, curr 和 next
    LinkListPtr prev = NULL;
    LinkListPtr curr = Q->front->next;
    LinkListPtr next = NULL;
    Q->rear = curr; // 新的队尾将是当前的队头

    // 反转链表
    while (curr != NULL) {
        next = curr->next; // 保存下一个节点
        curr->next = prev; // 反转当前节点的指针
        prev = curr; // 移动 prev 指针
        curr = next; // 移动 curr 指针
    }

    // 反转完成后，front 的 next 指向新的队头
    Q->front->next = prev;

    return OK;
}
// 约瑟夫环
void YueSeFu(int n, int k, int m) {
    LinkQueue Q;
    Init(&Q);

    for (int i = 1; i <= n; i++) {
        Add(&Q, i); // 用 A~Z 表示人
    }

    int count = 0; // 报数计数
    int currentPeople = n;
    ElemType temp;

    while (currentPeople > m) {
        DeAdd(&Q, &temp); // 出队
        count++;

        if (count == k) {
            // 第 k 人出局
            count = 0;
            currentPeople--;
        } else {
            // 没出局的重新排到队尾
            Add(&Q, temp);
        }
    }
    Get(&Q);
}


int main() {
    LinkQueue Q1,Q2;
    Status i;
    i = Init(&Q1);
    i = Init(&Q2);
    i = Add(&Q1,'A');
    i = Add(&Q1,'B');
    i = Add(&Q1,'C');
   
    i = Add(&Q2,'D');
    i = Add(&Q2,'E');
    i = Add(&Q2,'F');
  //  i = DeAdd(&Q);
    i = Get(&Q1);
    i = Link(&Q1,&Q2);
    i = Get(&Q1);
    i = Reverse(&Q1);
    i = Get(&Q1);
    return 0;
}