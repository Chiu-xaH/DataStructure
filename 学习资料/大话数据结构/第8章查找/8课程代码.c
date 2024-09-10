Status InsertAVL(BiTree *T,int e,Status *taller)
{  
	if(!*T)						/* 插入新结点，树“长高”，置taller为TRUE */ 
	{ 
		*T=(BiTree)malloc(sizeof(BiTNode));
		(*T)->data=e; 
		(*T)->lchild=(*T)->rchild=NULL; 
		(*T)->bf=EH;
		*taller=TRUE;
	}
	else
	{
		if (e==(*T)->data)		/* 树中已存在和e有相同关键字的结点则不再插入 */
		{  
			*taller=FALSE; 
			return FALSE;
		}
		if (e<(*T)->data)		/* 应继续在T的左子树中进行搜索 */
		{  
			if(!InsertAVL(&(*T)->lchild,e,taller)) /*  未插入 */ 
				return FALSE;
			if(*taller) 		/* 已插入到T的左子树中且左子树“长高” */ 
			{
				switch((*T)->bf)/* 检查T的平衡度 */ 
				{
					case LH: 	/* 原本左子树比右子树高，需要作左平衡处理 */ 
						LeftBalance(T);	
						*taller=FALSE; 
						break;
					case EH: 	/* 原本左、右子树等高，现因左子树增高而使树增高 */ 
						(*T)->bf=LH; 
						*taller=TRUE; 
						break;
					case RH: 	/* 原本右子树比左子树高，现左、右子树等高 */  
						(*T)->bf=EH; 
						*taller=FALSE; 
						break;
				}
			}
		}
		else					/*  应继续在T的右子树中进行搜索 */ 
		{ 
			if(!InsertAVL(&(*T)->rchild,e,taller)) /* 未插入 */ 
				return FALSE;
			if(*taller) 		/* 已插入到T的右子树且右子树“长高” */ 
			{
				switch((*T)->bf)/* 检查T的平衡度 */ 
				{
					case LH: 	/* 原本左子树比右子树高，现左、右子树等高 */ 
						(*T)->bf=EH; 
						*taller=FALSE;	
						break;
					case EH: 	/* 原本左、右子树等高，现因右子树增高而使树增高 */
						(*T)->bf=RH; 
						*taller=TRUE; 
						break;
					case RH: 	/* 原本右子树比左子树高，需要作右平衡处理 */ 
						RightBalance(T); 
						*taller=FALSE; 
						break;
				}
			}
		}
	}
	return TRUE;
}

void LeftBalance(BiTree *T)
{ 
	BiTree L,Lr;
	L=(*T)->lchild; 					/* L指向T的左子树根结点 */ 
	switch(L->bf)		/* 检查T的左子树的平衡度，并作相应平衡处理 */ 
	{ 
		 case LH:     	/* 新结点插入在T的左孩子的左子树上，要作单右旋处理 */ 
			(*T)->bf=L->bf=EH;
			R_Rotate(T);
			break;
		 case RH:     	/* 新结点插入在T的左孩子的右子树上，要作双旋处理 */ 
			Lr=L->rchild; 				/* Lr指向T的左孩子的右子树根 */ 
			switch(Lr->bf)				/* 修改T及其左孩子的平衡因子 */ 
			{ 							
				case LH: (*T)->bf=RH;
						 L->bf=EH;
						 break;
				case EH: (*T)->bf=L->bf=EH;
						 break;
				case RH: (*T)->bf=EH;
						 L->bf=LH;
						 break;
			}
			Lr->bf=EH;
			L_Rotate(&(*T)->lchild); 	/* 对T的左子树作左旋平衡处理 */ 
			R_Rotate(T); 				/* 对T作右旋平衡处理 */ 
	}
}

Status Delete(BiTree *p)
{/* 从二叉排序树中删除结点p，并重接它的左或右子树。 */
	BiTree q,s;
	if((*p)->rchild==NULL) /* 右子树空则只需重接它的左子树（待删结点是叶子也走此分支) */
	{
		q=*p; *p=(*p)->lchild; free(q);
	}
	else if((*p)->lchild==NULL) /* 只需重接它的右子树 */
	{
		q=*p; *p=(*p)->rchild; free(q);
	}
	else 						/* 左右子树均不空 */
	{
		q=*p; s=(*p)->lchild;
		while(s->rchild) 		/* 转左，然后向右到尽头（找待删结点的前驱）*/
		{
			q=s; s=s->rchild;
		}
		(*p)->data=s->data; /* s指向被删结点直接前驱(将被删结点前驱的值取代被删结点的值) */
		if(q!=*p)
			q->rchild=s->lchild;/*  重接q的右子树 */ 
		else
			q->lchild=s->lchild;/*  重接q的左子树 */
		free(s);
	}
	return TRUE;
}

Status DeleteBST(BiTree *T,int key)
{/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据结点 */
	if(!*T) 					/* 不存在关键字等于key的数据元素 */ 
		return FALSE;
	else
	{
		if (key==(*T)->data) 	/* 找到关键字等于key的数据元素 */ 
			return Delete(T);
		else if (key<(*T)->data)
			return DeleteBST(&(*T)->lchild,key);
		else
			return DeleteBST(&(*T)->rchild,key);
		 
	}
}

Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) 
{ /* 递归查找二叉排序树T中是否存在key, */ 
	if (!T)		/* 若查找不成功，指针p指向查找路径上访问的最后一个结点并返回FALSE */
	{ 
		*p = f;  
		return FALSE; 
	}
	else if (key==T->data) /* 若查找成功，则指针p指向该数据元素结点，并返回TRUE */
	{ 
		*p = T;  
		return TRUE; 
	} 
	else if (key<T->data) 
		return SearchBST(T->lchild, key, T, p);  	/* 在左子树中继续查找 */
	else  
		return SearchBST(T->rchild, key, T, p);  	/* 在右子树中继续查找 */
}

int Fibonacci_Search(int *a,int n,int key) /* 斐波那契查找 */
{
	int low,high,mid,i,k;
	low=1;						/* 定义最低下标为记录首位 */
	high=n;						/* 定义最高下标为记录末位 */
	k=0;
	while(n>F[k]-1)				/* 计算n位于斐波那契数列的位置 */
		k++;
	for (i=n;i<F[k]-1;i++)		/* 将不满的数值补全 */
		a[i]=a[n];
	while(low<=high)
	{
		mid=low+F[k-1]-1;		/* 计算当前分隔的下标 */
		if (key<a[mid])			/* 若查找记录小于当前分隔记录 */
		{
			high=mid-1;			/* 最高下标调整到分隔下标mid-1处 */
			k=k-1;				/* 斐波那契数列下标减一位 */
		}
		else if (key>a[mid])	/* 若查找记录大于当前分隔记录 */
		{
			low=mid+1;			/* 最低下标调整到分隔下标mid+1处 */
			k=k-2;				/* 斐波那契数列下标减两位 */
		}
		else
		{
			if (mid<=n)
				return mid;		/* 若相等则说明mid即为查找到的位置 */
			else 
				return n;		/* 若mid>n说明是补全数值，返回n */
		}
	}
	return 0;
}

/* 顺序查找，a为数组，n为要查找的数组个数，key为要查找的关键字 */
int Sequential_Search(int *a,int n,int key)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if (a[i]==key)
			return i;
	}
	return 0;
}

/* 有哨兵顺序查找 */
int Sequential_Search2(int *a,int n,int key)
{
	int i;
	a[0]=key;			/* 设置a[0]为关键字值，我们称之为“哨兵”*/
	i=n;				/* 循环从数组尾部开始 */
	while(a[i]!=key)
	{
		i--;
	}
	return i;			/* 返回0则说明查找失败 */
}

/* 折半查找 */
int Binary_Search(int *a,int n,int key)
{
	int low,high,mid;
	low=1;					/* 定义最低下标为记录首位 */
	high=n;					/* 定义最高下标为记录末位 */
	while(low<=high)
	{
		mid=(low+high)/2;	/* 折半 */
		if (key<a[mid])		/* 若查找值比中值小 */
			high=mid-1;		/* 最高下标调整到中位下标小一位 */
		else if (key>a[mid])/* 若查找值比中值大 */
			low=mid+1;		/* 最低下标调整到中位下标大一位 */
		else
		{
			return mid;		/* 若相等则说明mid即为查找到的位置 */
		}
	}
	return 0;
}

/* 插值查找 */
int Interpolation_Search(int *a,int n,int key)
{
	int low,high,mid;
	low=1;	/* 定义最低下标为记录首位 */
	high=n;	/* 定义最高下标为记录末位 */
	while(low<=high)
	{
		mid=low+ (high-low)*(key-a[low])/(a[high]-a[low]); /* 插值 */
		if (key<a[mid])		/* 若查找值比插值小 */
			high=mid-1;		/* 最高下标调整到插值下标小一位 */
		else if (key>a[mid])/* 若查找值比插值大 */
			low=mid+1;		/* 最低下标调整到插值下标大一位 */
		else
			return mid;		/* 若相等则说明mid即为查找到的位置 */
	}
	return 0;
}

/* 二叉树的二叉链表结点结构定义 */
typedef  struct BiTNode					/* 结点结构 */
{
	int data;							/* 结点数据 */
	struct BiTNode *lchild, *rchild;	/* 左右孩子指针 */
} BiTNode, *BiTree;


Status InsertBST(BiTree *T, int key) 
{  
	BiTree p,s;
	if (!SearchBST(*T, key, NULL, &p)) 	/* 查找不成功 */
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;  
		s->lchild = s->rchild = NULL;  
		if (!p) 
			*T = s;						/*  插入s为新的根结点 */
		else if (key<p->data) 
			p->lchild = s;				/*  插入s为左孩子 */
		else 
			p->rchild = s;  			/*  插入s为右孩子 */
		return TRUE;
	} 
	else 
		return FALSE;  					/*  树中已有关键字相同的结点，不再插入 */
}


int i;
int a[10]={62,88,58,47,35,73,51,99,37,93};
BiTree T=NULL;
for(i=0;i<10;i++)
{
	InsertBST(&T, a[i]);
}



/* 二叉树的二叉链表结点结构定义 */
typedef  struct BiTNode					/* 结点结构 */
{
	int data;							/* 结点数据 */
	int bf; 							/*  结点的平衡因子 */ 
	struct BiTNode *lchild, *rchild;	/* 左右孩子指针 */
} BiTNode, *BiTree;


/* 对以p为根的二叉排序树作右旋处理， */
/* 处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点 */
void R_Rotate(BiTree *P)
{ 
	BiTree L;
	L=(*P)->lchild; 		/*  L指向P的左子树根结点 */ 
	(*P)->lchild=L->rchild; /*  L的右子树挂接为P的左子树 */ 
	L->rchild=(*P);
	*P=L; 					/*  P指向新的根结点 */ 
}

/* 对以P为根的二叉排序树作左旋处理， */
/* 处理之后P指向新的树根结点，即旋转处理之前的右子树的根结点0  */
void L_Rotate(BiTree *P)
{ 
	BiTree R;
	R=(*P)->rchild; 		/*  R指向P的右子树根结点 */ 
	(*P)->rchild=R->lchild; /* R的左子树挂接为P的右子树 */ 
	R->lchild=(*P);
	*P=R; 					/*  P指向新的根结点 */ 
}

#define LH +1 /*  左高 */ 
#define EH 0  /*  等高 */ 
#define RH -1 /*  右高 */ 

/*  对以指针T所指结点为根的二叉树作左平衡旋转处理 */
/*  本算法结束时，指针T指向新的根结点 */



/*  对以指针T所指结点为根的二叉树作右平衡旋转处理， */ 
/*  本算法结束时，指针T指向新的根结点 */ 
void RightBalance(BiTree *T)
{ 
	BiTree R,Rl;
	R=(*T)->rchild; 					/* R指向T的右子树根结点 */ 
	switch(R->bf)
	{ /* 检查T的右子树的平衡度，并作相应平衡处理 */ 
	 case RH: /* 新结点插入在T的右孩子的右子树上，要作单左旋处理 */ 
			  (*T)->bf=R->bf=EH;
			  L_Rotate(T);
			  break;
	 case LH: /* 新结点插入在T的右孩子的左子树上，要作双旋处理 */ 
			  Rl=R->lchild; 			/* Rl指向T的右孩子的左子树根 */ 
			  switch(Rl->bf)			/* 修改T及其右孩子的平衡因子 */ 
			  { 						
				case RH: (*T)->bf=LH;
						 R->bf=EH;
						 break;
				case EH: (*T)->bf=R->bf=EH;
						 break;
				case LH: (*T)->bf=EH;
						 R->bf=RH;
						 break;
			  }
			  Rl->bf=EH;
			  R_Rotate(&(*T)->rchild); 	/* 对T的右子树作右旋平衡处理 */ 
			  L_Rotate(T); 				/* 对T作左旋平衡处理 */ 
	}
}



int i;
int a[10]={3,2,1,4,5,6,7,10,9,8};
BiTree T=NULL;
Status taller;
for(i=0;i<10;i++)
{
	InsertAVL(&T,a[i],&taller);
}


#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12 	/* 定义散列表长为数组的长度 */
#define NULLKEY -32768 

typedef struct
{
   int *elem; 			/* 数据元素存储基址，动态分配数组 */
   int count; 			/*  当前数据元素个数 */
}HashTable;

int m=0; 				/* 散列表表长，全局变量 */

/* 初始化散列表 */
Status InitHashTable(HashTable *H)
{
	int i;
	m=HASHSIZE;
	H->count=m;
	H->elem=(int *)malloc(m*sizeof(int));
	for(i=0;i<m;i++)
		H->elem[i]=NULLKEY; 
	return OK;
}

/* 散列函数 */
int Hash(int key)
{
	return key % m; /* 除留余数法 */
}

/* 插入关键字进散列表 */
void InsertHash(HashTable *H,int key)
{
	int addr = Hash(key); 				/* 求散列地址 */
	while (H->elem[addr] != NULLKEY) 	/* 如果不为空，则冲突 */
	{
		addr = (addr+1) % m; 			/* 开放定址法的线性探测 */
	}
	H->elem[addr] = key; 				/* 直到有空位后插入关键字 */
}


/* 散列表查找关键字 */
Status SearchHash(HashTable H,int key,int *addr)
{
	*addr = Hash(key);  									/* 求散列地址 */
	while(H.elem[*addr] != key) 							/* 如果不为空，则冲突 */
	{
		*addr = (*addr+1) % m; 								/* 开放定址法的线性探测 */
		if (H.elem[*addr] == NULLKEY || *addr == Hash(key)) /* 如果循环回到原点 */
			return UNSUCCESS;								/* 则说明关键字不存在 */
	}
	return SUCCESS;
}






