#include <stdio.h>
#include <stdbool.h>
/*
骑士游历问题：在国际棋盘上使一个骑士遍历所有的格子一遍且仅一遍，对于任意给定的顶点，输出一条符合上述要求的路径。
*/
#define N 8
//用于记录顺序，访问则+1
int cal = 0;
//棋盘
int chress[N][N] = {0};

void init() {
    cal = 0;
    chress[N][N] = {0};
}
//判断是否越界
bool isOut(int x,int y) {
    if(x >= 0 && x < N && y >= 0 && y < N) {
        return false;
    } else {
        return true;
    }
}
//判断是否访问过
bool isVisited(int x,int y) {
    return (chress[x][y] != 0);
}
//访问
void visit(int x,int y) {
    cal++;
    chress[x][y] = cal;
}
//打印棋盘(数字顺序升序则为骑士游历路线)
void printChress() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ",chress[i][j]);
        printf("\n");
    }
}
//DFS
void DFS(int x,int y) {
    //递归退出条件 访问完所有格子
    if(cal == N*N) {
        return;
    }
    if(isVisited(x,y) == false && isOut(x,y) == false) {
        //访问
        visit(x,y);
        //走法有八个方位
        DFS(x + 2, y + 1);    
        DFS(x - 2, y - 1);  
        DFS(x + 2, y - 1);    
        DFS(x - 2, y + 1);    
        DFS(x - 1, y - 2);  
        DFS(x + 1, y - 2);    
        DFS(x + 1, y + 2);    
        DFS(x - 1, y + 2);  
        return;
    } else {
        return;
    }
}

int main() {
    init();
    int x,y;
    printf("Input Start Position\n");
    
    scanf("%d %d",&x,&y);
    if (isOut(x,y)) {
        printf("isOut!\n");
    }
    DFS(x,y);
    printChress();
    return 0;
}