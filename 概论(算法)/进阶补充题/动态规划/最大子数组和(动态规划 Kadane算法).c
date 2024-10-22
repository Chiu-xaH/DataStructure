//参考资料 https://blog.csdn.net/weixin_43764974/article/details/134513506
#include <stdio.h>

int max(int a,int b) {
    return a > b ? a : b;
}

int Kadane(int array[],int size) {
    int maxEndingHere = array[0];
    int maxSoFar = array[0];
    for(int i = 1;i < size;i++) {
        maxEndingHere = max(maxEndingHere+array[i],array[i]);
        maxSoFar = max(maxSoFar,maxEndingHere);
    }
    return maxSoFar;
}

int main() {
    int array[4] = {9, 2, -6, 2};
    printf("%d",Kadane(array,4));
}