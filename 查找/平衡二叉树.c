#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100
#define SIZE 10

typedef int Status;
typedef int ElemType;

typedef struct TreeNode{
    ElemType data;
    int BH;//平衡因子
    struct TreeNode *leftChild,*rightChild;
} TreeNode,*Tree;
/////////插入操作//////////////////////////////////////////
//LL型 失衡结点的BH为2，失衡结点左孩子的BH为1 失衡结点右旋
//RR型 失衡结点的BH为-2，失衡结点右孩子的BH为-1 失衡结点左旋
//LR型 失衡结点的BH为2 失衡结点左孩子的BH为-1 失衡结点的左孩子进行左旋后，失衡结点右旋
//RL型 失衡结点的BH为-2，失衡结点右孩子的BH为1 失衡结点的右孩子进行右旋后，失衡结点左旋
//L+ R- BH=Height(Tree->leftChild)-Height(Tree->rightChild)
//多个结点失衡，调节离插入结点最近的结点

/*右旋[3] 顺时针旋转 冲突的右孩子变为旋转结点的左孩子
        3
    2   ->      2
1           1       3
*/

/*左旋[3] 逆时针旋转 冲突的左孩子变为旋转结点的右孩子
3
    2      ->       2
        1       3       1
*/

void RightRotate(Tree *T) {
    //旋转结点T，tree为最后要作为根的点
    Tree tree = (*T)->leftChild;
    //冲突的右孩子变为旋转结点的左孩子
    (*T)->leftChild = tree->rightChild;
    //tree最为根，旋转结点下去
    tree->rightChild = *T;
    *T = tree;
}

void LeftRotate(Tree *T) {
    Tree tree = (*T)->rightChild;
    (*T)->rightChild = tree->leftChild;
    tree->leftChild = *T;
    *T = tree;
}
