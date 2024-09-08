/*
第一次调用的参数push进堆栈，
原有递归代码外层加一个while循环，
判断条件就是递归结束的条件。
递归调用的地方改成push(); continue;
直到遇到递归终止条件，退出递归运算所在循环，
再用一个新的循环做出栈操作并计算，将递归代码中的return改成pop并执行响应的计算，
直到栈空为止。就可以了。
*/
#include <stdio.h>
#include "Stack.h"

// 递归A
void PA(int n) {
    if (n > 0) {
        PA(n - 1);
        printf("%d\n", n);
    }
}

// 非递归A
void PPA(int n) {
    Stack S;
    Init(&S);
    while (n > 0) {
        Push(&S, n);
        n--;
    }
    while (S.top != -1) {
        Elemtype E;
        Pop(&S, &E);
        printf("%d\n", E);
    }
}

// 递归B
void PB(int n) {
    if (n > 0) {
        printf("%d\n", n);
        PB(n - 1);
    }
}

//非递归B
void PPB(int n) {
    Stack S;
    Init(&S);
    L0:
    if (n > 0) {
        L1: {
            printf("%d\n", n);
        }
      //  Push(&S,n);
        n--;
        goto L0;
    }
   // while (S.top != -1) {
     //   Elemtype E;
       // Pop(&S, &E);
        //printf("%d\n", E);
    //}
}

int main() {
    // P(6);
    //PP(6);
    PPB(6);
    return 0;
}