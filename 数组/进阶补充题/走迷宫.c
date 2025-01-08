#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define N 50
#define M 50

typedef int Status;
#define OK 1;
#define  ERROR 0;

int a [N][M];

Status ReadFiles(int a[][M],int *n,int *m);
void Show(int a[][M],int n,int m);
void Update(int a[][M],int x,int y,int exitX,int exitY,int n,int m);

int main() {
    int n,m,status;
    printf("读取数据文件\n");
    status = ReadFiles(a,&n,&m);
    int x = 1,y = 1,exitX = 10,exitY = 11;

    if(status) {
        printf("加载完成!\n");
        printf("按键 A左移 S下移 D右移 W上移\n");
        Show(a,n,m);
        //printf("\n输入起点坐标 ");
       // scanf("%d %d",&x,&y);
        printf("\n");
        a[x][y] = 2;
        ///Show(a,n,m);
      //  printf("\n输入终点坐标 ");
      //  scanf("%d %d",&exitX,&exitY);
        Update(a,x,y,exitX,exitY,n,m);
    }
    else printf("无法打开文件");

    return 0;
}

Status ReadFiles(int a[][M],int *n,int *m) {
    FILE *fp;
    if((fp = fopen("Game.txt","r")) == NULL) {
        return ERROR;
    }
    fscanf(fp,"%d%d",n,m);
    for(int i = 0;i < *n;i++) {
        for(int j = 0;j < *m;j++) {
            fscanf(fp,"%d",&a[i][j]);
        }
    }
    fclose(fp);
    return OK;
}

void Show(int a[][M],int n,int m) {
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            if(a[i][j] == 1) {
                printf("■  ");
            } else if(a[i][j] == 0) {
                printf("   ");
            } else if(a[i][j] == 2) {
                printf("★  ");
            }
        }
        printf("\n");
    }
}

void Update(int a[][M],int x,int y,int exitX,int exitY,int n,int m) {
    char input;
    while (x != exitX || y != exitY) {
        system("cls");
        Show(a,n,m);
        Sleep(200);
        input = getch();
        //左移
        if(input == 'a' && a[x][y-1] != 1) {
            a[x][y] = 0;
            a[x][--y] = 2;
        }
        //右移
        if(input == 'd' && a[x][y+1] != 1) {
            a[x][y] = 0;
            a[x][++y] = 2;
        }
        //上移
        if(input == 'w' && a[x-1][y] != 1) {
            a[x][y] = 0;
            a[--x][y] = 2;
        }
        //下移
        if(input == 's' && a[x+1][y] != 1) {
            a[x][y] = 0;
            a[++x][y] = 2;
        }
    }
    system("cls");
    Show(a,n,m);
    Sleep(200);
    printf("你赢了");
    int xx;
    scanf("%d",xx);
}