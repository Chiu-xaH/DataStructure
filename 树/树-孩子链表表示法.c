#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
#define OK 1
#define ERROR 0

typedef int Status;
typedef char ElemType;

typedef struct Node {
    struct Node *next;
    ElemType data;
} Node,*LinkList;

typedef struct {
    ElemType data;
    LinkList firstChild;
} TreeHeadNode;

typedef struct {
    TreeHeadNode nodes[MAXSIZE];
    int nodeCount,rootPlace;
} Tree;

typedef struct TreeNode {
    ElemType data;
    struct TreeNode *leftChild,*rightChild;
} TreeNode,*BiTree;


//转换为二叉链表
/*树的结构
       A        A->B->C
      / \       B->D->E
     B   C      C->F->J
    /\  /\      D->H
   D E F J      E
  /   /\        F->I->G
 H   I G        G
 \              H->K
  K             I
                J
                K
   */

void Transfer(Tree T, BiTree *B) {
    // 初始化二叉树根节点
    *B = (BiTree)malloc(sizeof(TreeNode));
    (*B)->leftChild = (*B)->rightChild = NULL;
    (*B)->data = T.nodes[T.rootPlace].data;

    // 递归构建二叉树
    if (T.nodes[T.rootPlace].firstChild != NULL) {
        TransferChildren(T, *B, T.nodes[T.rootPlace].firstChild);
    }
}

void TransferChildren(Tree T, BiTree parent, LinkList childList) {
    if (childList == NULL) {
        return;
    }

    // 处理第一个孩子，作为左孩子
    BiTree currentChild = (BiTree)malloc(sizeof(TreeNode));
    currentChild->data = childList->data;
    currentChild->leftChild = currentChild->rightChild = NULL;
    parent->leftChild = currentChild;

    // 递归处理第一个孩子的子节点
    for (int i = 0; i < T.nodeCount; i++) {
        if (T.nodes[i].data == childList->data) {
            if (T.nodes[i].firstChild != NULL) {
                TransferChildren(T, currentChild, T.nodes[i].firstChild);
            }
            break;
        }
    }

    // 处理后续孩子，作为右孩子链表
    LinkList sibling = childList->next;
    while (sibling != NULL) {
        BiTree siblingNode = (BiTree)malloc(sizeof(TreeNode));
        siblingNode->data = sibling->data;
        siblingNode->leftChild = siblingNode->rightChild = NULL;
        currentChild->rightChild = siblingNode;
        currentChild = siblingNode;

        // 递归处理这个兄弟节点的子节点
        for (int i = 0; i < T.nodeCount; i++) {
            if (T.nodes[i].data == sibling->data) {
                if (T.nodes[i].firstChild != NULL) {
                    TransferChildren(T, siblingNode, T.nodes[i].firstChild);
                }
                break;
            }
        }
        sibling = sibling->next;
    }
}