#include <stdio.h>

int f(int n) {
    int res = 0;
    while(n != 0) {
        res += n;
        n--;
    }
    return res;
}
/*
已知数组A[n,n]是对称的
（1）设计算法将A[n,n]中的下三角中的各元素
    按行优先次序存储到一维数组B中。
（2）对任意输入的A数组中的元素的下标i, j，
    求解出该元素在B中的存储位置。
*/
void Question1() {
    int A[3][3] = {
        {9,1,4},
        {1,6,8},
        {4,8,7}
    };
    int B[f(3)];
    for(int i = 0;i < f(3);i++) {
        B[i] = 0;
    }
    int z = 0;
    for(int i = 0;i < 3;i++) {
        for(int j = 0;j <= i;j++) {
            B[z] = A[i][j];
            z++;
        }
    }
    for(int i = 0;i < z;i++) {
        //if(i == 1 || i == 3)
        //printf("| ");
        printf("%d ",B[i]);
    }
    int i,j;
    printf("\nInput i ang j of array A\n");
    scanf("%d %d",&i,&j);
    //交换
    if(i < j) {
        int temp = i;
        i = j;
        j = temp;
    }

    int res = (i + 1) * i / 2 + j;
    printf("Is in Array B [%d] = %d",res,B[res]);
}
/*
已知数组A[n,n]的上三角部分的各元素均为同一个值v0
 （1）设计算法将A[n,n]中的下三角中的各元素
    按行优先次序存储到一维数组B中，并将v0存放到其后面。
 （2）对任意输入的A数组中的元素的下标i, j，
    求解出该元素在B中的存储值。
*/
void Question2() {
    int v = 6;
    int A[4][4] = {
        {5,v, v,v},
        {6,7, v,v},
        {9,10,1,v},
        {2,8,12,3}
    };
    int Bint = f(4) + 1;
    int B[Bint];
    for(int i = 0;i < Bint;i++) {
        B[i] = 0;
    }
    int z = 0;
    for(int i = 0;i < 4;i++) {
        for(int j = 0;j <= i;j++) {
            B[z] = A[i][j];
            z++;
        }
    }
    B[f(4)] = v;
    for(int i = 0;i < Bint;i++) {
        printf("%d ",B[i]);
    }
    int i,j;
    printf("\nInput i ang j of array A\n");
    scanf("%d %d",&i,&j);
    if(i < j) {
        printf("Is in Array B [%d] = %d",f(4),v);
    } else {
        int res = (i + 1) * i / 2 + j;
        printf("Is in Array B [%d] = %d",res,B[res]);
    }
}
/*对两个以三元组形式存储的同阶稀疏矩阵A、B，
设计算法求C=A+B。*/
void Question3() {
    //见其他文件
}
int main() {
    Question2();
    return 0;
}


