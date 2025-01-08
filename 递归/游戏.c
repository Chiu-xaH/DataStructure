#include <stdio.h>
#include <stdbool.h>

const int xMax = 6,yMax = 3;
char step = '0';

char square[3][6] = {
    'N','E','E','S','W','E',
    'W','W','W','E','S','S',
    'S','N','W','W','W','W'
};

bool isOut(int x,int y) {
    return !(x >= 0 && x < xMax && y >= 0 && y < yMax);
}
//做标记
void visit(int x,int y) {
    square[y][x] = step++;
}

void printPath() {
    for(int i = 0;i < yMax;i++) {
        for(int j = 0;j < xMax;j++) {
          //  if(square[i][j] == 'O') {
            //    printf("%2c",'O');
           // } else {
                printf("%2c",square[i][j]);
           // }
        }
        printf("\n");
    }
}

//如果移动之后越界了，运动结束
void move(int x,int y) {
    if(isOut(x,y)) return;
    char opration = square[y][x];
    visit(x,y);
    if(opration == 'N') {
        move(x,y-1);
    } else if(opration == 'S') {
        move(x,y+1);
    } else if(opration == 'W') {
        move(x-1,y);
    } else if(opration == 'E') {
        move(x+1,y);
    } else {
        return;
    }
}

int main() {
    int x,y;
    printf("Input Start Pos(0<=X<6 0<=Y<3)\n");
    scanf("%d %d",&x,&y);
    
    if(!isOut(x,y)) {
        step = '0';
        move(x,y);
        printPath();
    } else {
        printf("IS OUT!");
    }
    return 0;
}