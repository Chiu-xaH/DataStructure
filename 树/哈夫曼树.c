#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OK 1
#define ERROR 0
#define SIZE 18
#define UNSIGN -1
#define MERGED -1
#define INFINITY 32758

typedef int Status;

typedef struct {
    char character;
    int frequency;
} NodeData;

typedef struct Node {
    struct Node *leftChild,*rightChild;
    NodeData data;
} Node,*Tree;

Status Init(Tree *T) {
    (*T) = NULL;
    return OK;
}
//创建结点，分配内存
Tree CreateNode(NodeData data) {
    Tree new = (Tree)malloc(sizeof(Node));
    new->data = data;
    new->leftChild = new->rightChild = NULL;
    return new;
}
//扫描一段字符串获得相关字符的权重
int Weight(char str[],Tree node[],int length) {
    int count[256];
    for(int i = 0;i < 256;i++) {
        count[i] = 0;
    }
    int i = 0,num = 0;
    while(i < length) {
        if(isalpha(str[i])) {
            count[(unsigned char)str[i]]++;
        }
        i++;
    }
    for(int i = 0;i < 256;i++) {
        if(count[i] > 0) {
            NodeData new;
            new.character = i;
            new.frequency = count[i];
            node[num] = CreateNode(new);
            num++;
        }
    }
    return num;
}
//按频率选择最小的两个
void SelectMin(Tree node[], int length, int *min1, int *min2) {
    *min1 = -1, *min2 = -1;
    for (int i = 0; i < length; i++) {
        if (node[i] == NULL) continue;
        if (*min1 == -1 || node[i]->data.frequency < node[*min1]->data.frequency) {
            *min2 = *min1;
            *min1 = i;
        } else if (*min2 == -1 || node[i]->data.frequency < node[*min2]->data.frequency) {
            *min2 = i;
        }
    }
}
Tree last;
//返回剩余未构建的数量
int lengths(Tree node[],int length) {
    int count = 0;
    for(int i = 0;i < length;i++) {
        if(node[i] != NULL) {
            count++;
            last = node[i];
        }
    }
    return count;
}
//构建哈夫曼树
void Create(Tree *T,Tree node[],int length) {
    //作为根节点
    if(lengths(node,length) == 1) {
        *T = last;
        return;
    }

    //找到两个小点的坐标
    int min1,min2;
    SelectMin(node,length,&min1,&min2);

    //构建三个点
    Tree right = node[min1];
    Tree left = node[min2];
    NodeData new;
    new.character = ' ';
    new.frequency = node[min1]->data.frequency + node[min2]->data.frequency;
    Tree root = CreateNode(new);
    root->leftChild = left;
    root->rightChild = right;

    //将两和添加到数组中，改长度
    node[min2] = root;
    //覆盖空
    node[min1] = NULL;

    //递归
    Create(T,node,length);
}
//前序遍历
void GetHead(Tree T) {
    if(T) {
        printf("%d ",T->data.frequency);
        GetHead(T->leftChild);
        GetHead(T->rightChild);
    }
}

void GetHeadChar(Tree T) {
    if(T) {
        if(T->data.character != ' ')
        printf("%c ",T->data.character);
        GetHeadChar(T->leftChild);
        GetHeadChar(T->rightChild);
    }
}
//设计算法输出哈夫曼树各叶子结点的编码
//左子树0，右子树1
int count = 0;
typedef struct {
    char *code;
    char character;
} HafumanCode;

HafumanCode codeArr[SIZE];
//存储到数组
void GetCode(Tree T,char code[],int length) {
    if(T == NULL) {
        return;
    }
    if(T->leftChild == NULL && T->rightChild == NULL) {
        code[length] = '\0';
        HafumanCode node;
        node.character = T->data.character;
        node.code = (char*)malloc(length * sizeof(char));
        strcpy(node.code,code);
        codeArr[count] = node;
        count++;
        return;
    }
    if(T->leftChild) {
        code[length] = '0';
        GetCode(T->leftChild,code,length+1);
    }
    if(T->rightChild) {
        code[length] = '1';
        GetCode(T->rightChild,code,length+1);
    }
}
//设计一个小系统，通过扫描一段字符串获得相关字符的权重，以此实现对文本的压缩，并同时构建出相应的解压缩功能，以还原所压缩文本
//编码
void Transfer(char str[],int len,char HfmCode[]) {
    //初始化
    HfmCode[0] = '\0';
    //转换
    int ptr = 0;
    while(str[ptr] != '\0') {
        for(int i = 0;i < count;i++) {
            if(codeArr[i].character == str[ptr]) {
                strcat(HfmCode,codeArr[i].code);
            }
        }
        ptr++;
    }
}
//解码
void Transfer2(Tree T,char str[],char HfmCode[]) {
    //初始化
    str[0] = '\0';
    //转换
    int ptr = 0;
    int n = 0;
    Tree tree = T;
    while(HfmCode[ptr] != '\0') {
        if(HfmCode[ptr] == '0') {
            tree = tree->leftChild;
        } else if(HfmCode[ptr] == '1') {
            tree = tree->rightChild;
        }
        if(tree->leftChild == NULL && tree->rightChild == NULL) {
            str[n] = tree->data.character;
            n++;
            tree = T;
        }
        ptr++;
    }
    str[n] = '\0';
}
//计算WPL
//找到每个叶子结点的路径长度（或者直接层序遍历？）
int len = 0;
int EveryLengths[100];
void EveryLength(Tree T,int count) {
    if(T->leftChild == NULL && T->rightChild == NULL) {
        EveryLengths[len] = count * T->data.frequency;
        len++;
    }
    if(T->leftChild) {
        EveryLength(T->leftChild,count+1);
    }
    if(T->rightChild) {
        EveryLength(T->rightChild,count+1);
    }
}
//求和
int WPL(Tree T) {
    EveryLength(T,0);
    int WPL = 0;
    for(int i = 0;i < len;i++) {
        WPL += EveryLengths[i];
    }
    return WPL;
}

int main() {
    char str[SIZE] = "ABAADCBC";
    Tree T;
    Init(&T);
    //构建树
    Tree node[SIZE];
    int length = Weight(str,node,8);
    Create(&T,node,length);
    //获得编码
   // char code[SIZE];
  //  GetCode(T,code,0);
//////////////////////////////////////////////////
    
   // char HfmCode[SIZE];
    //Transfer(str,8,HfmCode);
    //printf("%s\n",HfmCode);
   // char newStr[SIZE];
    //Transfer2(T,newStr,HfmCode);
   // printf("%s",newStr);
   printf("WPL = %d",WPL(T));
}