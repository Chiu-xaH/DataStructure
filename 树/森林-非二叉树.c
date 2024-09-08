#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define MAXSIZES 100 

typedef int Status;
typedef char ElemTypes;

typedef struct TreeNode {
    ElemTypes data;
    struct TreeNode *firstSon,*nextBrother;
} TreeNode,*Tree;
//定义一个数组存储每棵树根节点，表示森林
typedef struct {
    Tree root[MAXSIZES];
    int treeCount;
} Forest;

/* 用于构造树********************************** */
int treeIndex=1;
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

Status GetString(String S) {
    int length = S[0];
    for(int i = 1;i <= length;i++) {
        printf("%c",S[i]);
    }
    return OK;
}
//构造树，按顺序读取串，遇到#为空，按前序遍历的顺序放置树
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
		CreateTree(&(*T)->firstSon); 
		CreateTree(&(*T)->nextBrother); 
	}
}
/* ************************************************ */
Status InitTree(Tree *T) {
    (*T) = NULL;
    return OK;
}

Status InitForest(Forest *F) {
    F->treeCount = 0;
    for(int i = 0;i < MAXSIZES;i++) {
        F->root[i] = NULL;
    }
    return OK;
}

Status CreateForest(Forest *F) {
    if(F->treeCount >= MAXSIZES) {
        return ERROR;
    }
    Tree newTree;
    InitTree(&newTree);
    treeIndex = 1;
    CreateTree(&newTree);
    if(newTree) {
        F->root[F->treeCount] = newTree;
        (F->treeCount)++;
    }
    return OK;
}

Status GetHead(Tree T) {
    if(T != NULL) {
        printf("%c",T->data);
        GetHead(T->firstSon);
        GetHead(T->nextBrother);
        return OK;
    } else return ERROR;
}

Status GetTail(Tree T) {
    if(T != NULL) {
        GetTail(T->firstSon);
        GetTail(T->nextBrother);
        printf("%c",T->data);
        return OK;
    } else return ERROR;
}

void GetHeadForest(Forest F) {
    for(int i = 0;i < F.treeCount;i++) {
        GetHead(F.root[i]);
    }
}

void GetTailForest(Forest F) {
    for(int i = 0;i < F.treeCount;i++) {
        GetTail(F.root[i]);
    }
}

//层序遍历
typedef struct {
    Tree data[MAXSIZES];
    int front;
    int rear;
} Queue;

Status InitQueue(Queue *Q) {
    Q->front = 0;////<--
    Q->rear = 0;//////-->
    return OK;
}

Status Add(Queue *Q,Tree E) {
    if ((Q->rear + 1) % MAXSIZES == Q->front) {
        return ERROR;
    }	
	Q->data[Q->rear] = E;	
    Q->rear++;		
	Q->rear = Q->rear % MAXSIZES;
    return OK;
}

Status DeAdd(Queue *Q,Tree *E) {
    if(Q->front == Q->rear) {
        return ERROR;
    }
    *E = Q->data[Q->front];
    Q->front++;
    Q->front = Q->front % MAXSIZES;
    return OK;
}
//通用公式
int Length(Queue Q) {
    return (Q.rear-Q.front+MAXSIZES)%MAXSIZES;
}
//队列满-通用
Status isFull(Queue Q) {
    if((Q.rear+1)%MAXSIZES == Q.front) {
        return OK;
    } else {
        return ERROR;
    }
}
//队列空
Status isEmpty(Queue Q) {
    if(Q.front == Q.rear) {
        return OK;
    } else {
        return ERROR;
    }
}

void GetLayer(Tree T) {
    Queue Q;
    InitQueue(&Q);
    Add(&Q,T);
    while(!isEmpty(Q)) {
        Tree E;
        DeAdd(&Q,&E);
        printf("%c",E->data);
        if(E->firstSon) {
            Add(&Q,E->firstSon);
        }
        Tree sibling = E->firstSon;
        while(sibling) {
            if(sibling->nextBrother) {
                Add(&Q,sibling->nextBrother);
            }
            sibling = sibling->nextBrother;
        }
    }
}

void GetLayerForest(Forest F) {
    Queue Q;
    InitQueue(&Q);
    for(int i = 0;i < F.treeCount;i++)
    Add(&Q,F.root[i]);
    while(!isEmpty(Q)) {
        Tree E;
        DeAdd(&Q,&E);
        printf("%c",E->data);
        if(E->firstSon) {
            Add(&Q,E->firstSon);
        }
        Tree sibling = E->firstSon;
        while(sibling) {
            if(sibling->nextBrother) {
                Add(&Q,sibling->nextBrother);
            }
            sibling = sibling->nextBrother;
        }
    }
}

int HeightUpdate(Forest F) {
    Queue Q;
    InitQueue(&Q);
    int level = 0;
    int nodeCount = 0,nodeNextCount = 0;
    for(int i = 0;i < F.treeCount;i++) {
        Add(&Q,F.root[i]);
        nodeCount++;
    }
    
    while(!isEmpty(Q)) {
        Tree E;
        DeAdd(&Q,&E);
        nodeCount--;
        if(E->firstSon) {
            Add(&Q,E->firstSon);
            nodeNextCount++;
        }
        Tree sibling = E->firstSon;
        while(sibling) {
            if(sibling->nextBrother) {
                Add(&Q,sibling->nextBrother);
                nodeNextCount++;
            }
            sibling = sibling->nextBrother;
        }
        if(nodeCount == 0) {
            level++;
            nodeCount = nodeNextCount;
            nodeNextCount = 0;
        }
    }
    return level;
}

int leafCount = 0;
Status LeafCount(Tree T) {
    if(T != NULL) {
        if(T->firstSon == NULL) {
            leafCount++;
        } 
        LeafCount(T->firstSon);
        LeafCount(T->nextBrother);
        return OK;
    } else return ERROR;
}

//设计算法求树/森林中的叶子结点
Status GetLeaf(Tree T) {
    if(T != NULL) {
        if(T->firstSon == NULL) {
            printf("%c",T->data);
        } 
        GetLeaf(T->firstSon);
        GetLeaf(T->nextBrother);
        return OK;
    } else return ERROR;
}

//设计算法求树/森林的高度。
int max(int m,int n) {
    if(m >= n) {
        return m;
    } else {
        return n;
    }
}

int Height(Tree T) {
    if (T == NULL) {
        return ERROR;
    }

    int maxChildHeight = 0;
    Tree child = T->firstSon;

    while (child != NULL) {
        ///递归得到高度，赋值
        if (Height(child) > maxChildHeight) {
            maxChildHeight = Height(child);
        }
        //这一条边到底，去隔壁继续
        child = child->nextBrother;
    }

    return maxChildHeight + 1;
}

//5. 设计算法求树/森林中所有的父子对。
Status AllPC(Tree T) {
    Tree listFather = T;
    Tree list = listFather->firstSon;
    while(listFather) {
        while(list) {
            printf("(%c,%c)",listFather->data,list->data);
            list = list->nextBrother;
        }
        listFather = listFather->firstSon;
        list = listFather->firstSon;
    }
    return OK;
}

//设计算法按先序输出森林每个结点，并给出层次数
void GetHeadUpdate(Tree T,int level) {
    if(T != NULL) {
        printf("(%c,%d) ",T->data,level);
        GetHeadUpdate(T->firstSon,level+1);
        GetHeadUpdate(T->nextBrother,level);
        return OK;
    } else return ERROR;
}

void GetHeadUpdateForest(Forest F) {
    for(int i = 0;i < F.treeCount;i++) {
        GetHeadUpdate(F.root[i],1);
    }
}
//设计算法，森林转为广义表并输出（可选做）

void Question(Tree T,Tree parent,Tree preBrother) {
    if(parent != NULL && T == parent->firstSon) {
        printf("(%c,%c)\n",parent->data,T->data);
    } else if(preBrother != NULL) {
        printf("(%c,%c)\n",preBrother->data,T->data);
    }
    
    if(T->firstSon) {
        Question(T->firstSon,T,NULL);
    }
    if(T->nextBrother) {
        Question(T->nextBrother,parent,T);
    }
}

int main() {
    Status i;
    //Tree T;
    /*
       A            L       N
    / |   \         |
   B  C    D        M
  /\  |  / | \
 E F  G H  I J
 |
 K
      A
    /|\
   B C D
  /|    \
 E F     G
 ABE##F##C##DG####
    
    */
    Tree T;
    Forest F;
   i = InitTree(&T);
    InitForest(&F);
    //创建第一棵树
    //
    StrAssign(str,"ABEK##F##CG##DH#I#J####");
   // CreateForest(&F);
    CreateTree(&T);
    //创建第二棵树
  //  StrAssign(str,"LM###");
   // CreateForest(&F);
   
    //创建第三棵树
   // StrAssign(str,"N##");
   // CreateForest(&F);
    
   // i = GetHead(F.root[0]);
    //GetHeadForest(F);
    //GetLayer(F.root[0]);
    //GetLayerForest(F);
    //printf("HEIGHT %d",HeightUpdate(F));
  //  GetHeadUpdateForest(F);
   // printf("\n*********************\n");
   // i = LeafCount(T);
   // printf("Leaf count is %d",leafCount);
   // printf("\n*********************\n");
   // i = GetLeaf(T);
   // printf("\n*********************\n");
    //printf("Height = %d",Height(T));
     printf("\n*********************\n");
   //  i = AllPC(T);
   Question(T,NULL,NULL);
}
