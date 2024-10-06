int fib(int n){
    int n1 = 0,n2 = 1;
    int sum;
    for(int i = 0;i < n;i++) {
        sum = (n1+n2) % 1000000007;
        n1 = n2;
        n2 = sum;
    }
    return n1;
}
//斐波那契数列 动态规划算法