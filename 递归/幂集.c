//设计算法求集合｛1, 2, ..., n｝的幂集
#include<stdio.h>
#include<string.h>
#define MAXN 100

void dfs(int *a,int n,int i,int *x) {
    if(i >= n) {
        Output(a,n,x);
    } else {
        x[i] = 0;
        dfs(a,n,i+1,x);
        x[i] = 1;
        dfs(a,n,i+1,x);
    }
}
void Output(int *a,int n,int *x) {
    printf("{");
    for(int i = 0;i < n;i++) {
        if(x[i] ==  1)printf(" %d",a[i]);
    }
    printf(" } \n");
}

int main() {
    int a[]={ 1,2,3,4 };
    int n = sizeof(a) / sizeof(a[0]);
    int x[MAXN];
    memset(x,0,sizeof(x));
    dfs(a,n,0,x);
    return 0;
}


