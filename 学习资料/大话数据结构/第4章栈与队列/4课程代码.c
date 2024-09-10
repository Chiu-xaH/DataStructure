typedef int SElemType; 	/* SElemType类型根据实际情况而定，这里假设为int */

/* 顺序栈结构 */
typedef struct
{
        SElemType data[MAXSIZE];
        int top; 		/* 用于栈顶指针 */
}SqStack;

/* 插入元素e为新的栈顶元素 */
Status Push(SqStack *S,SElemType e)
{
    if(S->top == MAXSIZE -1) 	/* 栈满 */
    {
    	return ERROR;
    }
    S->top++;					/* 栈顶指针增加一 */
    S->data[S->top]=e;  		/* 将新插入元素赋值给栈顶空间 */
    return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqStack *S,SElemType *e)
{ 
    if(S->top==-1)
    	return ERROR;
    *e=S->data[S->top];		/* 将要删除的栈顶元素赋值给e */
    S->top--;				/* 栈顶指针减一 */
    return OK;
}

/* 两栈共享空间结构 */
typedef struct 
{
        SElemType data[MAXSIZE];
        int top1;	/* 栈1栈顶指针 */
        int top2;	/* 栈2栈顶指针 */
}SqDoubleStack;

/* 插入元素e为新的栈顶元素 */
Status Push(SqDoubleStack *S,SElemType e,int stackNumber)
{
    if (S->top1+1==S->top2)		/* 栈已满，不能再push新元素了 */
    	return ERROR;	
    if (stackNumber==1)			/* 栈1有元素进栈 */
        S->data[++S->top1]=e; 	/* 若是栈1则先top1+1后给数组元素赋值。 */
    else if (stackNumber==2)	/* 栈2有元素进栈 */
        S->data[--S->top2]=e; 	/* 若是栈2则先top2-1后给数组元素赋值。 */
    return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqDoubleStack *S,SElemType *e,int stackNumber)
{ 
    if (stackNumber==1) 
    {
        if (S->top1==-1) 
            return ERROR; 		/* 说明栈1已经是空栈，溢出 */
        *e=S->data[S->top1--]; 	/* 将栈1的栈顶元素出栈 */
    }
    else if (stackNumber==2)
    { 
        if (S->top2==MAXSIZE) 
            return ERROR; 		/* 说明栈2已经是空栈，溢出 */
        *e=S->data[S->top2++]; 	/* 将栈2的栈顶元素出栈 */
    }
    return OK;
}

/* 链栈结构 */
typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
}StackNode,*LinkStackPtr;


typedef struct
{
    LinkStackPtr top;
    int count;
}LinkStack;

/* 插入元素e为新的栈顶元素 */
Status Push(LinkStack *S,SElemType e)
{
    LinkStackPtr s=(LinkStackPtr)malloc(sizeof(StackNode)); 
    s->data=e; 
    s->next=S->top;	/* 把当前的栈顶元素赋值给新结点的直接后继，见图中① */
    S->top=s;  		/* 将新的结点s赋值给栈顶指针，见图中② */
    S->count++;
    return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(LinkStack *S,SElemType *e)
{ 
    LinkStackPtr p;
    if(StackEmpty(*S))
    	return ERROR;
    *e=S->top->data;
    p=S->top;				/* 将栈顶结点赋值给p，见图中③ */
    S->top=S->top->next;    /* 使得栈顶指针下移一位，指向后一结点，见图中④ */
    free(p);                /* 释放结点p */        
    S->count--;
    return OK;
}

int main()
{
	int i;
	int a[40];  
	a[0]=0;
	a[1]=1;
	printf("%d ",a[0]);  
	printf("%d ",a[1]);  
	for(i = 2;i < 40;i++)  
	{ 
		a[i] = a[i-1] + a[i-2];  
		printf("%d ",a[i]);  
	} 
    return 0;
}

/* 斐波那契的递归函数 */
int Fbi(int i)  
{
	if( i < 2 )
		return i == 0 ? 0 : 1;  
    return Fbi(i-1)+Fbi(i-2);  /* 这里Fbi就是函数自己，等于在调用自己 */
}  

int main()
{
	int i;
	printf("递归显示斐波那契数列：\n");
	for(i = 0;i < 40;i++)  
		printf("%d ", Fbi(i));  
    return 0;
}

typedef int QElemType; 	/* QElemType类型根据实际情况而定，这里假设为int */
/* 循环队列的顺序存储结构 */
typedef struct
{
	QElemType data[MAXSIZE];
	int front;    		/* 头指针 */
	int rear;			/* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
}SqQueue;

/* 初始化一个空队列Q */
Status InitQueue(SqQueue *Q)
{
	Q->front=0;
	Q->rear=0;
	return  OK;
}

/* 返回Q的元素个数，也就是队列的当前长度 */
int QueueLength(SqQueue Q)
{
	return  (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

/* 若队列未满，则插入元素e为Q新的队尾元素 */
Status EnQueue(SqQueue *Q,QElemType e)
{
	if ((Q->rear+1)%MAXSIZE == Q->front)	/* 队列满的判断 */
		return ERROR;
	Q->data[Q->rear]=e;						/* 将元素e赋值给队尾 */
	Q->rear=(Q->rear+1)%MAXSIZE;			/* rear指针向后移一位置， */
											/* 若到最后则转到数组头部 */
	return  OK;
}

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
Status DeQueue(SqQueue *Q,QElemType *e)
{
	if (Q->front == Q->rear)			/* 队列空的判断 */
		return ERROR;
	*e=Q->data[Q->front];				/* 将队头元素赋值给e */
	Q->front=(Q->front+1)%MAXSIZE;		/* front指针向后移一位置， */
										/* 若到最后则转到数组头部 */
	return  OK;
}

typedef int QElemType; 	/* QElemType类型根据实际情况而定，这里假设为int */

typedef struct QNode	/* 结点结构 */
{
   QElemType data;
   struct QNode *next;
}QNode,*QueuePtr;

typedef struct			/* 队列的链表结构 */
{
   QueuePtr front,rear; /* 队头、队尾指针 */
}LinkQueue;

/* 插入元素e为Q的新的队尾元素 */
Status EnQueue(LinkQueue *Q,QElemType e)
{ 
	QueuePtr s=(QueuePtr)malloc(sizeof(QNode));
	if(!s) 				/* 存储分配失败 */
		exit(OVERFLOW);
	s->data=e;
	s->next=NULL;
	Q->rear->next=s;	/* 把拥有元素e的新结点s赋值给原队尾结点的后继，见图中① */
	Q->rear=s;			/* 把当前的s设置为队尾结点，rear指向s，见图中② */
	return OK;
}

/* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
Status DeQueue(LinkQueue *Q,QElemType *e)
{
	QueuePtr p;
	if(Q->front==Q->rear)
		return ERROR;
	p=Q->front->next;		/* 将欲删除的队头结点暂存给p，见图中① */
	*e=p->data;				/* 将欲删除的队头结点的值赋值给e */
	Q->front->next=p->next;	/* 将原队头结点的后继p->next赋值给头结点后继，见图中② */
	if(Q->rear==p)			/* 若队头就是队尾，则删除后将rear指向头结点，见图中③ */
		Q->rear=Q->front;
	free(p);
	return OK;
}


