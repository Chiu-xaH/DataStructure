#include <stdio.h>

int Step(int n) {
    if(n == 1) {
        return 1;
    }
    if(n == 2) {
        return 2;
    }
    return Step(n-1) + Step(n-2);
}
int main() {
    //int n =;
    printf("%d",Step(8));
    return 0;
}
//补充：如果用动态规划算法能更快，感兴趣自学一下动态规划
//力扣第70题
int climbStairs(int n) {
    if(n == 1) {
        return 1;
    }
    if(n == 2) {
        return 2;
    }
    //上一步结果 上两步结果
    int prev1 = 1, prev2 = 2;
    for (int i = 3; i <= n; i++) {
        int current = prev1 + prev2;
        prev1 = prev2;
        prev2 = current;
    }
    return prev2;
}
