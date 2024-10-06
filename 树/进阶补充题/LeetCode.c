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