#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 20
#define SIZE 5

typedef int Status;
typedef int Elemtype;
typedef struct {
    int top;
    Elemtype data[MAXSIZE];
} Stack;

Status Init(Stack *S) {
    S->top = -1;
    return OK;
}

Status Push(Stack *S,Elemtype E) {
    if(S->top == MAXSIZE) {
        return ERROR;
    }
    S->top++;
    S->data[S->top] = E;
    return OK;
}

Status Pop(Stack *S,Elemtype *E) {
    if(S->top == -1) {
        return ERROR;
    }
    *E = S->data[S->top];
    S->top--;
    return OK;
}

Status Get(Stack *S) {
    if(S->top == -1) {
        return ERROR;
    }
   
    for(int i = S->top;i > -1;i--) {
        printf("%d ",S->data[i]);
    }
    printf("]\n");
    return OK;
}

Status Length(Stack S) {
    return S.top + 1;
}

/*
对一个栈的输入序列a1, a2, a3, …, an，
称由此栈依次出栈后所得到的元素序列为栈的合法输出序列。
例如: 假设栈S的一个输入序列为1, 2, 3, 4, 5，
则可得到多个输出序列，如1, 2, 3, 4, 5就是一个合法的输出序列，
同理， 5, 4, 3, 2, 1和3, 2, 1, 4, 5也分别是其合法的输出序列。
分别求解下列问题：
（1）判断序列1, 3, 4, 5, 2是否是合法的输出序列;
（2）对输入序列1, 2, 3, 4, 5，求出其所有的合法的输出序列;
（3）设计算法以判断对输入序列1, 2, 3, …, n，
    序列a1, a2, a3,   …, an是否是该栈的合法的输出序列（假设输出序列在数组A中）;
（4）给出栈的合法的输出序列的规律。
*/


// 求所有合法序列
// 自己扩展 考试不考，但是要记住能生成多少个合法序列，在笔记文件夹里有！
int count = 0;
void BackTrack(int maxNum,int nextNum, Stack* stack, Stack* out) 
{
    // 已经完成出栈 
	if (Length(*stack) == 0 && nextNum > maxNum) {
		Get(out);
        count++;
		return;
	}
    // 可以出栈,遍历这一步进行出栈的情况
	if(Length(*stack) > 0) {
        Elemtype E1,E2;
        // 出栈
        Pop(stack,&E1);
		Push(out,E1);
        // 遍历
		BackTrack(maxNum, nextNum, stack, out);
        // 恢复现场
        Pop(out,&E2);
		Push(stack,E2);
	}
    // 可以入栈，遍历这一步进行入栈的情况
	if (nextNum <= maxNum) {
        // 入栈
		Push(stack, nextNum);
        // 遍历
		BackTrack(maxNum, nextNum + 1, stack, out);
        // 恢复现场
        Elemtype E;
		Pop(stack,&E);
	}
}

void AllStackOutput(int n) {
    // 初始化
    Stack stack;
	Stack out;
    Init(&stack);
    Init(&out);
    count = 0;
    // 开始
	BackTrack(n, 1, &stack, &out);
    printf("Total: %d\n",count);
}


// 判断是否为合法输出
Status isStack(int arr[],int length) {
    for(int i = 0;i < length-1;i++) {
        int elem = arr[i];
        int ptr = i;
        int newArray[MAXSIZE];
        int count = 0;
        while(ptr < length) {
            if(arr[ptr] < elem) {
                newArray[count] = arr[ptr];
                count++;
            }
            ptr++;
        }
       
        ptr = 0;
        while(ptr + 1 < count) {
            if(newArray[ptr] < newArray[ptr+1]) {
                return ERROR;
            }
            ptr++;
        }
    }
    return OK;
}

int main() {
   Status i;
   
   int size = 5;
//    printf("Input how many you want to? ");
//    scanf("%d",&size);

//    int arr[size];

//    printf("Input the number\n");
//    for(int i = 0;i < size;i++) {
//      scanf("%d",&arr[i]);
//    }
//     i = isStack(arr,size);

//     if(i) {
//         printf("Is a right stack");
//     } else {
//         printf("Is a false stack");
//     }

AllStackOutput(5);    
    return 0;
}