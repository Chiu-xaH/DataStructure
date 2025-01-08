#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <synchapi.h>

#define M 4
#define N 4
#define OK 1
#define ERROR 0

typedef int Status;
int arr[M][N] = {0};

int Up(int arr[M][N]);
int Down(int arr[M][N]);
int Right(int arr[M][N]);
int Left(int arr[M][N]);
void Show(int arr[M][N]);
void GetTwo(int arr[M][N]);
void Move(int arr[M][N]);




void Show(int arr[M][N]) {
    for(int i = 0;i < M;i++) {
        for(int j =0;j < N;j++) {
            printf("%5d",arr[i][j]);
        }
        printf("\n");
    }
}

void GetTwo(int arr[M][N]) {
    while(1) {
        int numM = rand() % 4;
        int numN = rand() % 4;
        int num = rand() % 2;
        int list[2] = {2,4};
        if(arr[numM][numN] == 0) {
            arr[numM][numN] = list[num];
             break;
        }
    }
}

void Move(int arr[M][N]) {
    char input;

    while (1) {
        system("cls");
        Show(arr);
        Sleep(200);
        input = getch();
        //◊Û“∆
        if(input == 'a' || input == 'A') {
            int up = Left(arr);
            if(up == 1) {
                GetTwo(arr);
            }
        }
        //”““∆
        if(input == 'd' || input == 'D') {
            int up = Right(arr);
            if(up == 1) {
                GetTwo(arr);
            }
        }
        //…œ“∆
        if(input == 'w' || input == 'W') {
            int up = Up(arr);
            if(up == 1) {
                GetTwo(arr);
            }
        }
        //œ¬“∆
        if(input == 's' || input == 'S') {
            int up = Down(arr);
            if(up == 1) {
                GetTwo(arr);
            }
        }
    }
}

int Full(int arr[M][N]) {
    int full = 0;
    for(int i = 0;i < M;i++) {
        for(int j = 0;j < N;j++) {
            if(arr[i][j] == 0) {
                full++;
            }
        }
    }
    return full;
}

int Up(int arr[M][N]) {
    int change = 0;
    int k,now,next;
    for(int j = 0;j < N;j++) {
        for(int i = 0;i <M;i++) {
            now = arr[i][j];
            if(now != 0) {
                k = i + 1;
                while(k < N) {
                    next = arr[k][j];
                    if(next != 0) {
                       if(next == now) {
                            arr[i][j] = 2 * arr[k][j];
                            arr[k][j] = 0;
                            change = 1;
                       }
                       k = N;
                    }
                    k++;
                }
            }
        }
    }
    for(int j = 0; j < N;j++) {
        for(int i = 0;i < M;i++) {
            now = arr[i][j];
            if(now == 0) {
                k = i + 1;
                while(k < N) {
                    next = arr[k][j];
                    if(next != 0) {
                        change = 1;
                        arr[i][j] = next;
                        arr[k][j] = 0;
                        k = N;
                    }
                    k++;
                }
            }
        }
    }
    return change;
}
int Down(int arr[M][N]) {
    int change = 0;
    int k,now,next;
    for(int j = 0;j < N;j++) {
        for(int i = M - 1;i >= 0;i--) {
            now = arr[i][j];
            if(now != 0) {
                k = i - 1;
                while(k >= 0) {
                    next = arr[k][j];
                    if(next != 0) {
                       if(next == now) {
                            arr[i][j] = 2 * arr[k][j];
                            arr[k][j] = 0;
                            change = 1;
                       }
                       k = -1;
                    }
                    k--;
                }
            }
        }
    }
    for(int j = 0; j < N;j++) {
        for(int i = M - 1;i >= 0;i--) {
            now = arr[i][j];
            if(now == 0) {
                k = i - 1;
                while(k >= 0) {
                    next = arr[k][j];
                    if(next != 0) {
                        change = 1;
                        arr[i][j] = next;
                        arr[k][j] = 0;
                        k = -1;
                    }
                    k--;
                }
            }
        }
    }
    return change;
}
int Left(int arr[M][N]) {
    int change = 0;
    int k,now,next;
    for(int i = 0;i < M;i++) {
         for(int j = 0;j < N;j++){
            now = arr[i][j];
            if(now != 0) {
                k = j + 1;
                while(k < M) {
                    next = arr[i][k];
                    if(next != 0) {
                       if(next == now) {
                            arr[i][j] = 2 * arr[i][k];
                            arr[i][k] = 0;
                            change = 1;
                       }
                       k = M;
                    }
                    k++;
                }
            }
        }
    }
    for(int i = 0;i < M;i++) {
        for(int j = 0; j < N;j++) {
            now = arr[i][j];
            if(now == 0) {
                k = j + 1;
                while(k < M) {
                    next = arr[i][k];
                    if(next != 0) {
                        change = 1;
                        arr[i][j] = next;
                        arr[i][k] = 0;
                        k = M;
                    }
                    k++;
                }
            }
        }
    }
    return change;
}
int Right(int arr[M][N]) {
    int change = 0;
    int k,now,next;
    for(int i = M - 1;i >= 0;i--) {
        for(int j = 0;j < N;j++) {
            now = arr[i][j];
            if(now != 0) {
                k = j - 1;
                while(k >= 0) {
                    next = arr[i][k];
                    if(next != 0) {
                       if(next == now) {
                            arr[i][j] = 2 * arr[i][k];
                            arr[i][k] = 0;
                            change = 1;
                       }
                       k = -1;
                    }
                    k--;
                }
            }
        }
    }
     for(int i = M - 1;i >= 0;i--) {
        for(int j = 0;j < N;j++) {
            now = arr[i][j];
            if(now == 0) {
                k = j - 1;
                while(k >= 0) {
                    next = arr[i][k];
                    if(next != 0) {
                        change = 1;
                        arr[i][j] = next;
                        arr[i][k] = 0;
                        k = -1;
                    }
                    k--;
                }
            }
        }
    }
    return change;
}


int main() {
    printf("ª∂”≠¿¥µΩ 2048\n");
    printf("∞¥º¸ A◊Û“∆ Sœ¬“∆ D”““∆ W…œ“∆\n");
    GetTwo(arr);
    Move(arr);
}