#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100 
#define MAX_TREE_SIZE 100

typedef int Status;
typedef int ElemType;
typedef ElemType Tree[MAX_TREE_SIZE];
 /* 0号单元存储根结点  */
typedef struct {
	int level,order; 
    /* 结点的层,本层序号(按满二叉树计算) */
} Position;

ElemType Nil=0;//以0为空

Status Init(Tree T) {
    for(int i = 0;i < MAX_TREE_SIZE;i++) {
        T[i] = Nil;
    }
    return OK;
}

Status Create(Tree T) {
    int i = 0;
 	printf("Input Value(INT) of Node According to CengXu ,0 is NULL,999 is Over.Node Num <= %d:\n",MAX_TREE_SIZE);
	while(i<10) {
		T[i] = i + 1;
		//此结点(不空)无双亲且不是根
		if(
            i != 0 &&
            T[(i+1)/2-1] == Nil && 
            T[i] != Nil
            ) {
			printf("No parents and No Root Node %d\n",T[i]);
			exit(0);
		}
		i++;
	}
	while(i<MAX_TREE_SIZE) {
		T[i] = Nil;
		i++;
	}
	return OK;
}

void Head(Tree T,int e) {
    printf("%d",T[e]);
    if(T[2*e+1] != Nil) {
        Head(T,2*e+1);
        //左子树
    }
    if(T[2*e+2] != Nil) {
        Head(T,2*e+2);
        //右子树
    }
}

Status GetHead(Tree T) {
    if(T[0] != Nil) {
        Head(T,0);
    }
    printf("\n");
    return OK;
}

int main() {
    /*树的结构
       A   
      / \ 
     B   C 
    /\  /\
   D E F J
  /   /\
 H   I G
 \
  K
    */
    Status i;
    Tree T;
    i = Init(T);
    i = Create(T);
    i = GetHead(T);
}


