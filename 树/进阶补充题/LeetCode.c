#include <stdio.h>
#include <stdlib.h>

const int true = 1,false = 0;
typedef int bool;

struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};

//最小深度：从根节点到最近叶子节点的最短路径上的节点数量。
int min(int m,int n) {
    return m < n ? m : n;
}

int minDepth(struct TreeNode* root) {
    if(root==NULL) return 0;
    if(root->left == NULL) return 1 + minDepth(root->right);
    if(root->right == NULL) return 1 + minDepth(root->left);
    // 如果左右子树都不为空，返回左右子树最小深度 + 1
    return 1 + min(minDepth(root->left), minDepth(root->right));
}

//翻转二叉树
void PreOrder(struct TreeNode * root) {
    if(root) {
        struct TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

struct TreeNode* invertTree(struct TreeNode* root) {
    PreOrder(root);
    return root;
}


//判断是否是对称二叉树
bool isMirror(struct TreeNode* left,struct TreeNode* right) {
    if(left == NULL && right == NULL) {
        return true;
    } else if(left != NULL && right == NULL) {
        return false;
    } else if(left == NULL && right != NULL) {
        return false;
    } else  {
        //核心思想：细化成最小子问题
        //左子树的左子树对称为右子树的右子树，左子树的右子树对称为右子树的左子树
        bool structEqual = isMirror(left->left,right->right) && isMirror(right->left,left->right);
        bool valEqual = (left->val == right->val);
        return valEqual && structEqual;
    }
}

bool isSymmetric(struct TreeNode* root) {
    if(root) {
       return isMirror(root->left,root->right);
    }
    return true;
}

//判断是否是相同树
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if(p && q) {
        bool valEqual = (p->val == q->val);
        bool structEqual = isSameTree(p->left,q->left) && isSameTree(p->right,q->right);
        return valEqual && structEqual;
    } else if(!p && !q) {
        return true;
    } else {
        return false;
    }
}

//判断是否为AVL树
int max(int a,int b) {
    return a > b ? a : b;
}

int Height(struct TreeNode* root) {
    if(root) {
        return 1 + max(Height(root->left),Height(root->right));
    } else return 0;
}

int BH(struct TreeNode* root) {
    int left = Height(root->left);
    int right = Height(root->right);
    return left - right;
}

bool isBalanced(struct TreeNode* root) {
    if (!root) return true;
    int bh = BH(root);
    bool structEqual = isBalanced(root->left) && isBalanced(root->right);
    return (fabs(bh) <= 1) && structEqual;
}

//判断是否是堂兄弟结点（父节点不同，但深度相同）
 //思路：先找到x和y结点的父节点，父节点不同但深度相同则为堂兄弟
struct TreeNode* PreOrder(struct TreeNode* root,struct TreeNode* parent,int a) {
    if(root) {
        if(root->val == a) {
            return parent;
        }
        if(PreOrder(root->left,root,a)) return PreOrder(root->left,root,a);
        return PreOrder(root->right,root,a);
    }
    return NULL;
}
int Height(struct TreeNode* root,int a) {
    if (root == NULL) return -1;
    if (root->val == a) return 0;
    int leftHeight = Height(root->left,a);
    if (leftHeight != -1) return leftHeight + 1;

    int rightHeight = Height(root->right, a);
    if (rightHeight != -1) return rightHeight + 1;

    return -1;
}

bool isCousins(struct TreeNode* root, int x, int y) {
    struct TreeNode* parentX = PreOrder(root,NULL,x);
    struct TreeNode* parentY = PreOrder(root,NULL,y);
    if(parentX != parentY && Height(root,x) == Height(root,y)) {
        return true;
    } else {
        return false;
    }
}
//计算左叶子总和数
void PreOrder(struct TreeNode* root,int *total) {
    if(root) {
        if(root->left && root->left->left == NULL && root->left->right == NULL) {
            *total += root->left->val;
        }
        PreOrder(root->left,total);
        PreOrder(root->right,total);
    }
    
}
 
int sumOfLeftLeaves(struct TreeNode* root) {
    int total = 0;
    PreOrder(root,&total);
    return total;
}

 //二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。
//两节点之间路径的 长度 由它们之间边数表示。

 //思路：直径=根左子树高度+根右子树高度
 //子树高度用递归或者遍历思想
 int max(int a,int b) {
    return a > b ? a : b;
 }
int Height(struct TreeNode* root,int *dis) {
    if(root) {
        int left = Height(root->left,dis);
        int right = Height(root->right,dis);
        *dis = max(*dis,left+right);
        return 1 + max(left,right);
    } else return 0;
}

int diameterOfBinaryTree(struct TreeNode* root) {
    int dis = 0;
    Height(root,&dis);
    return dis;
}
//判断sub是否是root子树
bool isSameTree(struct TreeNode* s, struct TreeNode* t) {
    if (!s && !t) return true;
    if (!s || !t) return false;
    return (s->val == t->val) && isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
}

bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
    if (!root) return false;
    if (isSameTree(root, subRoot)) return true;
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}
