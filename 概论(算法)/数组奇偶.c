/*设计算法将整型数组A[n]中的元素调整为左右两部分，
其中左边所有元素为奇数，右边所有元素为偶数。并要求算法的时间复杂度为O(n)。
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

void Swap(int A[], int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void q3(int A[], int n) {
    //处理分成三部分
    int left = 0, right = n - 1;
    int cur = left;
    // 第一次，把%3==0的移到最左边
    while (cur <= right) {
        if (A[cur] % 3 == 0) {
            Swap(A, cur, left);
            left++;
            cur++;
        } else {
            cur++;
        }
    }
    // 现在 left 是 %3!=0 的起点
    cur = left;
    // 第二次，把%3==1的移到中间
    while (cur <= right) {
        if (A[cur] % 3 == 1) {
            Swap(A, cur, left);
            left++;
            cur++;
        } else {
            cur++;
        }
    }
}

void q2(int A[],int n) {
    //处理分成两部分
    int left = 0,right = n - 1;
    while (left < right) {
        // 左边是奇数，符合要求，继续往右走
        if (A[left] % 2 == 1) {
            left++;
        }
        // 右边是偶数，符合要求，继续往左走
        else if (A[right] % 2 == 0) {
            right--;
        }
        // 左边是偶数，右边是奇数，需要交换
        else {
            Swap(A, left, right);
            left++;
            right--;
        }
    }
}

int main()
{
    int A[SIZE];
    for (int i = 0; i < SIZE; i++) {
        A[i] = rand() % 20;
    }
    printf("Original Array \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", A[i]);
    }

    q2(A,SIZE);

    printf("\nOperated Array \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", A[i]);
    }
    return 0;
}