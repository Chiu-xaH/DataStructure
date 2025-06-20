
#include <stdio.h>
#include <stdlib.h>

/* 树的双亲表示法结点结构定义 */
#define MAX_TREE_SIZE 100

typedef int TElemType;				/* 树结点的数据类型，目前暂定为整型 */

typedef struct PTNode				/* 结点结构 */
{
	TElemType data;					/* 结点数据 */
	int parent;						/* 双亲位置 */
} PTNode;

typedef struct						/* 树结构 */
{
	PTNode nodes[MAX_TREE_SIZE];	/* 结点数组 */
	int r,n;						/* 根的位置和结点数 */
} PTree;


/* 树的孩子表示法结构定义 */
#define MAX_TREE_SIZE 100

typedef int TElemType;			/* 树结点的数据类型，目前暂定为整型 */

typedef struct CTNode			/* 孩子结点 */
{
	int child;	
	struct CTNode *next;	
} *ChildPtr;

typedef struct 					/* 表头结构 */
{
	TElemType data;	
	ChildPtr firstchild;	
} CTBox;

typedef struct	     			/* 树结构 */
{
	CTBox nodes[MAX_TREE_SIZE];	/* 结点数组 */
	int r,n;					/* 根的位置和结点数 */
} CTree;



/* 树的孩子兄弟表示法结构定义 */
typedef struct CSNode
{
	TElemType data;	
	struct CSNode *firstchild,*rightsib;	
} CSNode,*CSTree;



/* 二叉树的二叉链表结点结构定义 */
typedef struct BiTNode  			/* 结点结构 */
{
   TElemType data;					/* 结点数据 */
   struct BiTNode *lchild,*rchild; 	/* 左右孩子指针 */
}BiTNode,*BiTree;


/* 二叉树的前序遍历递归算法 */
/* 初始条件: 二叉树T存在 */
/* 操作结果: 前序递归遍历T */
void PreOrderTraverse(BiTree T)
{ 
	if(T==NULL)
		return;
	printf("%c",T->data);		/* 显示结点数据，可以更改为其它对结点操作 */
	PreOrderTraverse(T->lchild);/* 再先序遍历左子树 */
	PreOrderTraverse(T->rchild);/* 最后先序遍历右子树 */
}

/* 二叉树的中序遍历递归算法 */
/* 初始条件: 二叉树T存在 */
/* 操作结果: 中序递归遍历T */
void InOrderTraverse(BiTree T)
{ 
	if(T==NULL)
		return;
	InOrderTraverse(T->lchild); /* 中序遍历左子树 */
	printf("%c",T->data);		/* 显示结点数据，可以更改为其它对结点操作 */
	InOrderTraverse(T->rchild); /* 最后中序遍历右子树 */
}

/* 二叉树的后序遍历递归算法 */
/* 初始条件: 二叉树T存在 */
/* 操作结果: 后序递归遍历T */
void PostOrderTraverse(BiTree T)
{
	if(T==NULL)
		return;
	PostOrderTraverse(T->lchild); 	/* 先后序遍历左子树  */
	PostOrderTraverse(T->rchild); 	/* 再后序遍历右子树  */
	printf("%c",T->data);			/* 显示结点数据，可以更改为其它对结点操作 */
}

/* 按前序输入二叉树中结点的值（一个字符） */
/* #表示空树，构造二叉链表表示二叉树T。 */
void CreateBiTree(BiTree *T)
{ 
	TElemType ch;
	
	scanf("%c",&ch);
	ch=str[index++];

	if(ch=='#') 
		*T=NULL;
	else
	{
		*T=(BiTree)malloc(sizeof(BiTNode));
		if(!*T)
			exit(OVERFLOW);
		(*T)->data=ch; 					/* 生成根结点 */
		CreateBiTree(&(*T)->lchild); 	/* 构造左子树 */
		CreateBiTree(&(*T)->rchild); 	/* 构造右子树 */
	}
}

/* 二叉树的二叉线索存储结构定义 */
typedef char TElemType;
typedef enum {Link,Thread} PointerTag;	/* Link=0表示指向左右孩子指针, */
										/* Thread=1表示指向前驱或后继的线索 */
typedef  struct BiThrNode				/* 二叉线索存储结点结构 */
{
	TElemType data;						/* 结点数据 */
	struct BiThrNode *lchild, *rchild;	/* 左右孩子指针 */
	PointerTag LTag;
	PointerTag RTag;					/* 左右标志 */
} BiThrNode, *BiThrTree;


BiThrTree pre; 					/* 全局变量,始终指向刚刚访问过的结点 */
/* 中序遍历进行中序线索化 */
void InThreading(BiThrTree p)
{ 
	if(p)
	{
		InThreading(p->lchild); /* 递归左子树线索化 */
		if(!p->lchild) 			/* 没有左孩子 */
		{
			p->LTag=Thread; 	/* 前驱线索 */
			p->lchild=pre; 		/* 左孩子指针指向前驱 */
		}
		if(!pre->rchild) 		/* 前驱没有右孩子 */
		{
			pre->RTag=Thread; 	/* 后继线索 */
			pre->rchild=p; 		/* 前驱右孩子指针指向后继(当前结点p) */
		}
		pre=p; 					/* 保持pre指向p的前驱 */
		InThreading(p->rchild); /* 递归右子树线索化 */
	}
}













































































































































































































































































































































































































































































































































































































































































































































































































































































/* T指向头结点，头结点左链lchild指向根结点，头结点右链rchild指向中序遍历的*/
/* 最后一个结点。中序遍历二叉线索链表表示的二叉树T */
Status InOrderTraverse_Thr(BiThrTree T)
{ 
	BiThrTree p;
	p=T->lchild; 					/* p指向根结点 */
	while(p!=T)						/* 空树或遍历结束时,p==T */
	{ 
		while(p->LTag==Link)		/*当LTag==0时循环到中序序列第一个结点 */
			p=p->lchild;
		printf（"%c",p->data）; 		/* 显示结点数据，可以更改为其他对结点操作 */
		while(p->RTag==Thread && p->rchild!=T)
		{
			p=p->rchild;
			printf（"%c",p->data）;	/* 访问后继结点 */
		}
		p=p->rchild;				/*  p进至其右子树根 */
	}
	return OK;
}


if （a<60）
	b=＂不及格＂;
else if （a<70）
	b=＂及格＂;
else if （a<80）
	b=＂中等＂;
else if （a<90）
	b=＂良好＂;
else 
	b=＂优秀＂;



