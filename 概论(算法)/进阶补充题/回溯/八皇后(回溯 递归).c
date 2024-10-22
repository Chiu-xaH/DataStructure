#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 8

int chessBoard[N];  // chessBoard[i] 表示第i行皇后所在的列
int solutions = 0;  // 统计解的个数

//判断是否可以在第row行第col列放置皇后
bool isCan(int row,int col) {
    for (int i = 0; i < row; i++) {
        //检查同列或对角线是否有冲突
        if (chessBoard[i] == col || 
        //对角线上下的皇后 == 循环所在位置
        abs(chessBoard[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

//使用回溯算法放置皇后
void solve(int row) {
    if (row == N) {
        //所有行都已成功放置
        solutions++;
        return;
    }

    //尝试在第row行的每一列放置皇后
    for (int col = 0; col < N; col++) {
        if (isCan(row, col)) {
            chessBoard[row] = col;  //放置皇后
            solve(row + 1);         //递归处理下一行
        }
    }
}

int main() {
    solve(0);  //从第0行开始放置
    printf("Total %d", solutions);
    return 0;
}
