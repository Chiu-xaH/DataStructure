#include <stdio.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 10

typedef int Status;
typedef int Elemtype;
typedef struct {
    Elemtype data[MAXSIZE];
    int front;
    int rear;
} Queue;

Status Init(Queue *Q) {
    Q->front = 0;/////<--
    Q->rear = 0;//////-->
    return OK;
}

Status Add(Queue *Q,Elemtype E) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return ERROR;
    }	
	Q->data[Q->rear] = E;	
    Q->rear++;		
	Q->rear = Q->rear % MAXSIZE;
    return OK;
}

Status DeAdd(Queue *Q) {
    if(Q->front == Q->rear) {
        return ERROR;
    }
    Q->front++;
    Q->front = Q->front % MAXSIZE;
    return OK;
}

Status Get(Queue *Q) {
    if(Q->front == Q->rear) {
        return ERROR;
    }
    int i = Q->front;
    while(i != Q->rear) {
        printf("%d ",Q->data[i]);
        i++;
        i = i % MAXSIZE;
    }
    printf("\n");
    return OK;
}

int Length(Queue *Q) {
    int i = Q->front;
    int length = 0;
    while(i != Q->rear) {
        i++;
        i = i % MAXSIZE;
        length++;
    }
    return length;
}

int GetTwo(Queue *Q) {
    int firstIndex = Q->front;
    int secondIndex = (Q->front + 1) % MAXSIZE;
    
    int result = Q->data[firstIndex] + Q->data[secondIndex];
    return result;
}

/*设计算法，用队列计算并打印杨辉三角的前8行的内容，即输出结果如下
                          1
                      1      1
                  1      2     1
              1      3      3     1
           1     4      6      4     1
        1     5     10    10    5     1
     1     6     15   20    15    6     1
  1     7    21   35    35    21    7     1

分析：杨辉三角的规律
每行的第一和最后一个数是1，
从第3行开始的其余的数是上一行对应位置的左右两个数的和。
例如：第7行的第3个数15是第6行中的第2和第3两个数5和10的和。
由此可知：可用上一行的数来求出对应位置的下一行的内容。
为此，可用队列来保存上一行的内容。
每当由上一行的两个数求出下一行的一个数时，其中的前一个便可以删除，而新求出的数就要入队。
*/
/*
1
1     1
1     2     1
1     3     3     1
1     4     6     4     1
1     5     10    10    5     1
1     6     15    20    15    6     1
1     7     21    35    35    21    7     1
*/
int main() {
    Status I;
    Queue Q[8];
    for(int j = 0;j < 8;j++) 
        I = Init(&Q[j]);
///////////////////////////////////
    for(int j = 0;j < 8;j++) {
        //处理前两行特殊情况
        if(j == 0) {
            I = Add(&Q[j],1);
        }
        if(j == 1) {
            I = Add(&Q[j],1);
            I = Add(&Q[j],1);
        }
        //正式开始算法
        if(j > 1) {
            //初始化
            int length = Length(&Q[j - 1]);
            Q[j] = Q[j-1];
        }
        if(j > 1) {
            int length = Length(&Q[j]);
            for(int k = 0;k < length - 1;k++) {
                int result = GetTwo(&Q[j]);
                I = Add(&Q[j],result);
                I = DeAdd(&Q[j]);
            }
            //尾插一个1
            I = Add(&Q[j],1);
        }
        //打印
        I = Get(&Q[j]);
    }

    return 0;
}
