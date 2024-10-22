#include <stdio.h>
#define MAX 100

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

int maxSubmatrixSum(int M[4][4],int m,int n) {
    int maxTotal = M[0][0];
    int dp[n];  // 用于存储列的累加和
    
    for(int i = 0;i < m;i++) {
        for(int j = 0;j < n;j++) {
            dp[j] = 0;
        }
        for(int j = i;j < n;j++) {
            for(int k = 0;k < n;k++) {
                dp[k] += M[j][k];
            }
            maxTotal = max(Kadane(dp,n),maxTotal);
        }
    }
    return maxTotal;
}

int main() {
    int M[4][4] = {
        {0, -2, -7, 0},
        {9, 2, -6, 2},
        {-4, 1, -4, 1},
        {-1, 8, 0, -2}
    };
 
    int result = maxSubmatrixSum(M,4,4);

    printf("%d", result);
}