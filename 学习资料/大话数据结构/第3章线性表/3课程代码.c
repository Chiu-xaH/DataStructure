Status ListInsert(StaticLinkList L, int i, ElemType e)   
{  
	int j, k, l;   
	k = MAXSIZE - 1;   					/* 注意k首先是最后一个元素的下标 */
	if (i < 1 || i > ListLength(L) + 1)   
		return ERROR;   
	j = Malloc_SSL(L);   				/* 获得空闲分量的下标 */
	if (j)   
	{   
		L[j].data = e;   				/* 将数据赋值给此分量的data */
		for(l = 1; l <= i - 1; l++)   	/* 找到第i个元素之前的位置 */
		   k = L[k].cur;           
		L[j].cur = L[k].cur;    		/* 把第i个元素之前的cur赋值给新元素的cur */
		L[k].cur = j;           		/* 把新元素的下标赋值给第i个元素之前元素的ur */
		return OK;   
	}   
	return ERROR;   
}

/*将所有的在线性表Lb中但不在La中的数据元素插入到La中*/
void unionL(SqList *La,SqList Lb)
{
	int La_len,Lb_len,i;
	ElemType e;                        /*声明与La和Lb相同的数据元素e*/
	La_len=ListLength(*La);            /*求线性表的长度 */
	Lb_len=ListLength(Lb);
	for (i=1;i<=Lb_len;i++)
	{
		GetElem(Lb,i,&e);              /*取Lb中第i个数据元素赋给e*/
		if (!LocateElem(*La,e))        /*La中不存在和e相同数据元素*/
			ListInsert(La,++La_len,e); /*插入*/
	}
}



#define MAXSIZE 20          /* 存储空间初始分配量 */
typedef int ElemType;       /* ElemType类型根据实际情况而定，这里为int */
typedef struct
{
	ElemType data[MAXSIZE]; /* 数组，存储数据元素 */
	int length;             /* 线性表当前长度 */
}SqList;


#define OK 1
#define ERROR 0
/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;         

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值，注意i是指位置，第1个位置的数组是从0开始 */
Status GetElem(SqList L,int i,ElemType *e)
{
	if(L.length==0 || i<1 || i>L.length)
		return ERROR;
	*e=L.data[i-1];

	return OK;
}

/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(SqList *L,int i,ElemType e)
{ 
	int k;
	if (L->length==MAXSIZE)  			/* 顺序线性表已经满 */
		return ERROR;
	if (i<1 || i>L->length+1)			/* 当i比第一位置小或者比最后一位置后一位置还要大时 */
		return ERROR;				

	if (i<=L->length)        			/* 若插入数据位置不在表尾 */
	{
		for(k=L->length-1;k>=i-1;k--)  	/* 将要插入位置后的元素向后移一位 */
			L->data[k+1]=L->data[k];
	}
	L->data[i-1]=e;          			/* 将新元素插入 */
	L->length++;

	return OK;
}


/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(SqList *L,int i,ElemType *e) 
{ 
	int k;
	if (L->length==0)               /* 线性表为空 */
		return ERROR;
	if (i<1 || i>L->length)         /* 删除位置不正确 */
		return ERROR;
	*e=L->data[i-1];
	if (i<L->length)                /* 如果删除不是最后位置 */
	{
		for(k=i;k<L->length;k++)	/* 将删除位置后继元素前移 */
			L->data[k-1]=L->data[k];
	}
	L->length--;
	return OK;
}

/* 线性表的单链表存储结构 */
typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node;
typedef struct Node *LinkList; /* 定义LinkList */


/* 初始条件：链式线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem(LinkList L,int i,ElemType *e)
{
	int j;
	LinkList p;		/* 声明一结点p */
	p = L->next;		/* 让p指向链表L的第一个结点 */
	j = 1;		/*  j为计数器 */
	while (p && j<i)  /* p不为空或者计数器j还没有等于i时，循环继续 */
	{   
		p = p->next;  /* 让p指向下一个结点 */
		++j;
	}
	if ( !p || j>i ) 
		return ERROR;  /*  第i个元素不存在 */
	*e = p->data;   /*  取第i个元素的数据 */
	return OK;
}


s->next = p->next;    /* 将p的后继结点赋值给s的后继  */
p->next = s;          /* 将s赋值给p的后继 */


/* 初始条件：链式线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(LinkList *L,int i,ElemType e)
{ 
	int j;
	LinkList p,s;
	p = *L;   
	j = 1;
	while (p && j < i)     				/* 寻找第i个结点 */
	{
		p = p->next;
		++j;
	} 
	if (!p || j > i) 
		return ERROR;   				/* 第i个元素不存在 */

	s = (LinkList)malloc(sizeof(Node)); /* 生成新结点(C语言标准函数) */
	s->data = e;  
	s->next = p->next;    				/* 将p的后继结点赋值给s的后继 */
	p->next = s;          				/* 将s赋值给p的后继 */
	return OK;
}

q = p->next;
p->next = q->next;			/* 将q的后继赋值给p的后继 */


/* 初始条件：链式线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(LinkList *L,int i,ElemType *e) 
{ 
	int j;
	LinkList p,q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* 遍历寻找第i个元素 */
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i) 
		return ERROR;           /* 第i个元素不存在 */
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继 */
	*e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	return OK;
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（头插法） */
void CreateListHead(LinkList *L, int n) 
{
	LinkList p;
	int i;
	srand(time(0));                         /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;                      /* 先建立一个带头结点的单链表 */
	for (i=0; i<n; i++) 
	{
		p = (LinkList)malloc(sizeof(Node)); /* 生成新结点 */
		p->data = rand()%100+1;             /* 随机生成100以内的数字 */
		p->next = (*L)->next;    
		(*L)->next = p;						/* 插入到表头 */
	}
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n) 
{
	LinkList p,r;
	int i;
	srand(time(0));                     	/* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node)); 	/* L为整个线性表 */
	r=*L;                                	/* r为指向尾部的结点 */
	for (i=0; i<n; i++) 
	{
		p = (Node *)malloc(sizeof(Node)); 	/* 生成新结点 */
		p->data = rand()%100+1;           	/* 随机生成100以内的数字 */
		r->next=p;                        	/* 将表尾终端结点的指针指向新结点 */
		r = p;                            	/* 将当前的新结点定义为表尾终端结点 */
	}
	r->next = NULL;                       	/* 表示当前链表结束 */
}


/* 初始条件：链式线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{ 
	LinkList p,q;
	p=(*L)->next;           /*  p指向第一个结点 */
	while(p)                /*  没到表尾 */
	{
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;        /* 头结点指针域为空 */
	return OK;
}


#define MAXSIZE 1000 	/* 存储空间初始分配量 */

/* 线性表的静态链表存储结构 */
typedef struct 
{
	ElemType data;
	int cur;  			/* 游标(Cursor) ，为0时表示无指向 */
} Component,StaticLinkList[MAXSIZE];



/* 将一维数组space中各分量链成一个备用链表，space[0].cur为头指针，"0"表示空指针 */
Status InitList(StaticLinkList space) 
{
	int i;
	for (i=0; i<MAXSIZE-1; i++)  
		space[i].cur = i+1;
	space[MAXSIZE-1].cur = 0; 	/* 目前静态链表为空，最后一个元素的cur为0 */
	return OK;
}

/* 若备用空间链表非空，则返回分配的结点下标，否则返回0 */
int Malloc_SSL(StaticLinkList space) 
{ 
	int i = space[0].cur;           		/* 当前数组第一个元素的cur存的值 */
											/* 就是要返回的第一个备用空闲的下标 */
	if (space[0]. cur)         
		space[0]. cur = space[i].cur;       /* 由于要拿出一个分量来使用了， */
											/* 所以我们就得把它的下一个 */
											/* 分量用来做备用 */
	return i;
}

/*  删除在L中第i个数据元素   */
Status ListDelete(StaticLinkList L, int i)   
{ 
	int j, k;   
	if (i < 1 || i > ListLength(L))   
		return ERROR;   
	k = MAXSIZE - 1;   
	for (j = 1; j <= i - 1; j++)   
		k = L[k].cur;   
	j = L[k].cur;   
	L[k].cur = L[j].cur;   
	Free_SSL(L, j);   
	return OK;   
} 

/*  将下标为k的空闲结点回收到备用链表 */
void Free_SSL(StaticLinkList space, int k) 
{  
	space[k].cur = space[0].cur;    /* 把第一个元素的cur值赋给要删除的分量cur */
	space[0].cur = k;               /* 把要删除的分量下标赋值给第一个元素的cur */
}

/* 初始条件：静态链表L已存在。操作结果：返回L中数据元素个数 */
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

p=rearA->next;   			    /* 保存A表的头结点，即① */
rearA->next=rearB->next->next;	/* 将本是指向B表的第一个结点（不是头结点）*/
                 				/* 赋值给reaA->next，即② */
q=rearB->next;
rearB->next=p;				   	/* 将原A表的头结点赋值给rearB->next，即③ */
free（q）;					   	/* 释放q */



/*线性表的双向链表存储结构*/
typedef struct DulNode
{
		ElemType data;
		struct DuLNode *prior;    	/*直接前驱指针*/
		struct DuLNode *next;		/*直接后继指针*/
} DulNode, *DuLinkList;


p->next->prior = p = p->prior->next

s - >prior = p;   			/*把p赋值给s的前驱，如图中①*/
s -> next = p -> next;		/*把p->next赋值给s的后继，如图中②*/
p -> next -> prior = s;		/*把s赋值给p->next的前驱，如图中③*/
p -> next = s;				/*把s赋值给p的后继，如图中④*/


p->prior->next=p->next;   	/*把p->next赋值给p->prior的后继，如图中①*/
p->next->prior=p->prior;	/*把p->prior赋值给p->next的前驱，如图中②*/
free（p）;					/*释放结点*/














































































































































































































































































































































































































































































































































































































































































































































































