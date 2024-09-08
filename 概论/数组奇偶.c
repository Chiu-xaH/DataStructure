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

void q(int A[], int n) {
    int left = 0, right = n - 1;
    while (left != right) {
        if (A[left] % 3 == 0)
            left++;
        else
            Swap(A, left, right);
        if (A[left] % 3 != 0)
            right--;
        else
            Swap(A, left, right);
    }
    right = n - 1;
    while (left != right) {
        if (A[left] % 3 == 1)
            left++;
        else
            Swap(A, left, right);
        if (A[left] % 3 == 2)
            right--;
        else
            Swap(A, left, right);
    }
}
int main()
{
    int A[SIZE];
    for (int i = 0; i < SIZE; i++) {
        A[i] = rand() % 100;
    }
    printf("Original Array \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", A[i]);
    }
    /*
    int left = 0,right = SIZE - 1;
    while(left < right) {

        if(A[left] % 2 == 1) {
            left++;
        }
        if(A[right] % 2 == 0) {
            right--;
        }
        if(A[left] % 2 == 0 && left < right) {
            int temp;
            temp = A[left];
            A[left] = A[right];
            A[right] = temp;
        } else if(A[right] % 2 == 1 && left < right) {
            int temp;
            temp = A[left];
            A[left] = A[right];
            A[right] = temp;
        }
    }

*/
    q(A, SIZE);
    printf("\nOperated Array \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", A[i]);
    }
    return 0;
}