#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define CHILD 0
#define THREAD 1
#define MAXSIZES 100 

typedef int Status;
typedef int Tag; 
typedef char ElemTypes;

typedef struct TreeNode {
    ElemTypes data;
    Tag leftTag,rightTag;
    struct TreeNode *leftChild,*rightChild;
} TreeNode,*Tree;

Status Init(Tree *T) {
    (*T) = NULL;
    return OK;
}

/* 用于构造二叉树********************************** */
int treeIndex = 1;
typedef char String[24]; /*  0号单元存放串的长度 */
String str;
//字符char转化为串String
Status StrAssign(String T,char *chars) { 
	if(strlen(chars)>MAXSIZES) {
        return ERROR;
    } else {
		T[0] = strlen(chars);
		for(int i = 1;i <= T[0]; i++)
			T[i]= *(chars+i-1);
		return OK;
	}
}
//构造二叉树，按顺序读取串，遇到#为空，按前序遍历的顺序放置树
void CreateTree(Tree *T) { 
	ElemTypes ch;
    //从1开始，每次递归递增，移动到下一个元素
	ch=str[treeIndex++];

	if(ch=='#') {
        *T=NULL;
    } else {
		*T= (Tree)malloc(sizeof(TreeNode));
		if(!*T) exit(0);
        //采用前序遍历的方法构造
		(*T)->data=ch; /* 生成根结点 */
        //构造子树
		CreateTree(&(*T)->leftChild); 
		CreateTree(&(*T)->rightChild); 
	}
}

/* ************************************************ */

Status GetHead(Tree T) {
    if(T != NULL) {
        printf("%c",T->data);
        GetHead(T->leftChild);
        GetHead(T->rightChild);
        return OK;
    } else return ERROR;
}

Status GetMiddle(Tree T) {
    if(T != NULL) {
        GetMiddle(T->leftChild);
        printf("%c",T->data);
        GetMiddle(T->rightChild);
        return OK;
    } else return ERROR;
}

Status GetTail(Tree T) {
    if(T != NULL) {
        GetTail(T->leftChild);
        GetTail(T->rightChild);
        printf("%c",T->data);
        return OK;
    } else return ERROR;
}

Tree treePre = NULL;

//构建线索化
void MiddleThread(Tree T) {
    if(T != NULL) {
        MiddleThread(T->leftChild);
        if(T->leftChild == NULL) {
            T->leftTag = THREAD;
            T->leftChild = treePre;
        }
        if(
          treePre != NULL && 
          treePre->rightChild == NULL) {
            treePre->rightTag = THREAD;
            treePre->rightChild = T;
        }
        treePre = T;
        MiddleThread(T->rightChild);
    }
}

//线索二叉树中序遍历
Status GetThreadMiddle(Tree T) {
    Tree tree = T;
    while (
        tree != NULL && 
        tree->leftTag == CHILD) {
            tree = tree->leftChild;
    }
    while (tree != NULL) {
        printf("%c", tree->data);
        if (tree->rightTag == THREAD) {
            tree = tree->rightChild;
        } else {
            tree = tree->rightChild;
            while (tree != NULL && tree->leftTag == CHILD) {
                tree = tree->leftChild;
            }
        }
    }
    return OK;
}

// 前序构建线索化
void HeadThread(Tree T) {
    if(T != NULL) {
        
        if(T->leftChild == NULL) {
            T->leftChild = treePre;
            T->leftTag = THREAD;
        }
        
        if(treePre != NULL) {
            if(treePre->rightChild == NULL) {
                treePre->rightChild = T;
                treePre->rightTag = THREAD;
            } else {
                
            }   
        }
       
        treePre = T;
        
        if(T->leftTag == CHILD) {
            HeadThread(T->leftChild);
        }
        if(T->rightTag == CHILD) {
            HeadThread(T->rightChild);
        }
    }
}
// 线索二叉树前序遍历
void GetHeadThread(Tree T) {
    Tree tree = T;
    while(tree) {
        printf("%c",tree->data);
        if(tree->leftTag == CHILD) {
            tree = tree->leftChild;
        } else {
            tree = tree->rightChild;  
        }
    } 
}


/*树的结构ABCDEFGHIJ 
       A   
      / \ 
     B   F  
    /\  /\
   C D G  I 
    / /   \
   E H    J
    */
 /*  A
    / \
   B  E
  /\
 C D
*/
  //CDBEA 
//设计算法，将值为data的结点作为右子树的（后序序列的）第一个节点的左孩子插入到后序线索二叉树
void Insert(Tree T,ElemTypes data) {
    treePre = NULL;
    Tree newNode = (Tree)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->leftTag = THREAD;
    newNode->rightTag = THREAD;
    newNode->rightChild = NULL;
    newNode->leftChild = NULL;
    Tree tree = T;
    while(tree) {
        treePre = tree;
        if(tree->leftTag == CHILD) {
            tree = tree->leftChild;
        } else if (tree->rightTag == CHILD) {
            tree = tree->rightChild;
        } else {
            break;
        }
    }
    if(treePre) {
        if(treePre->leftTag == THREAD) {
            treePre->leftChild = newNode;
            
        }
    }
}

int main() {
    Status i;
    Tree T;
    i = Init(&T);
    /*树的结构
       A   
      / \ 
     B   F  
    /\  /\
   C D G  I 
    / /   \
   E H    J
    */
 /*  A
    / \
   B  E
  /\
 C D
*/
   //ABC##DE###FGH###I#J##
    StrAssign(str,"ABC##D##E##");
	CreateTree(&T);
   // i = GetMiddle(T);
   // printf("\n*************\n");
    //MiddleThread(T);

    //i = GetThreadMiddle(T);
    treePre = NULL;
    Init(&treePre);
    HeadThread(T);
    //printf("%c",T->leftChild->leftChild->rightChild->data);
    GetHeadThread(T);
    printf("\n*************\n");
}