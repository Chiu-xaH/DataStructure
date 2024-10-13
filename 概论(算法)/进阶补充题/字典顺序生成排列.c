//设计算法按字典顺序输出123...n所有序列
//例如n=3,123,132,213,231,312,321
#include <stdio.h>

void Swap(int *a,int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Reverse(int array[],int left,int right) {
    while(left < right) {
        Swap(&array[left],&array[right]);
        left++;
        right--;
    }
}

void Print(int array[],int n) {
    for(int i = 0;i < n;i++) {
        printf("%d",array[i]);
    }
    printf("\n");
}

// 找到字典序的下一个排列
int nextPermutation(int arr[], int n) {
    // 从右往左找到第一个arr[i] < arr[i+1]的元素
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    // 如果没有这样的i，说明已经是最后一个排列
    if (i < 0) {
        return 0;
    }

    // 从右往左找到第一个比arr[i]大的arr[j]
    int j = n - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }
    // 交换arr[i]和arr[j]
    Swap(&arr[i], &arr[j]);
    // 反转arr[i+1]到arr[n-1]的部分
    Reverse(arr, i + 1, n - 1);

    return 1;
}

void PrintA(int n) {
    int str[n];
    //初始化
    for(int i = 0;i < n;i++) {
        str[i] = i+1;
    }
    Print(str,n);
    while (nextPermutation(str, n)) {
        Print(str, n);
    }
}

int main() {
    PrintA(5);
}