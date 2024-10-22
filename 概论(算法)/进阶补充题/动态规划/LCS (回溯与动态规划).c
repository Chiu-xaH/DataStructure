#include <stdio.h>
#include <string.h>

#define MAX 100

// 回溯找到最长公共子序列
void findLCS(char X[], char Y[], int m, int n, int dp[MAX][MAX]) {
    int i = m, j = n;
    char lcs[MAX];
    int index = dp[m][n]; //长度
    lcs[index] = '\0';

    //从dp表中回溯最长公共子序列
    while (i > 0 && j > 0) {
        //字符相同
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        //不相等 根据dp值选择向上或向左
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    printf("%s\n", lcs);
}

void LCS(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);
    int dp[MAX][MAX]; 

    //初始化
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= n; i++) {
        dp[0][n] = 0;
    }
    //赋值
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            //字符对应上了
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                //找它的左侧和上面，选最大的
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    //最后一个格子就是匹配长度
    // 回溯找到LCS
    findLCS(X, Y, m, n, dp);
}

int main() {
    char X[] = "china";
    char Y[] = "indoor";
    LCS(X, Y);
    return 0;
}
