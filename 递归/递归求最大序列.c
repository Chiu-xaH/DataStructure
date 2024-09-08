/*已知输入序列中各元素的值至少有两个元素。
设计算法求出该序列中元素的所有最大升、降子序列。
例如：若元素依次为（1，20，30，12，3，5，7，4，6，100，11，8），
则输出结果为（1，20，30），（30，12，3），（3，5，7），（7，4），（4，6，100），（100，11，8）。*/
#include <stdio.h>

void sort(int arr[],int size,int i,int j) {

    printf("( %d ",arr[i]);
    for(i,j;j < size - 1,i < size;j++,i++) {
        int c = 0;
            
        if(arr[i] < arr[j]) {
            printf("%d ",arr[j]); 
        } else c = 1;
        if(c == 1) break;
    }
    printf("),( %d ",arr[i]);
    for(i,j;j < size - 1,i < size;j++,i++) {
        int c = 0;
            
        if(arr[i] > arr[j]) {
               
            printf("%d ",arr[j]); 
        } else c = 1;
        if(c == 1) {
            break;
        }
    }
    printf(")");

    if(j <= size - 1) {
        printf(",");
        sort(arr,size,i,j);
    }
}
int main() {
    int size = 12;
    int arr[] = {1,20,30,12,3,5,7,4,6,100,11,8};
    int i = 0,j = 1;
    sort(arr,size,i,j);
}