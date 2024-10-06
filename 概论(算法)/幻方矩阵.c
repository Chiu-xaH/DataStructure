/*
将1～n2放在n*n (n为奇数) 的方阵中，使得任意一行  
任意一列以及两条对角线上的所有元素之和均相等。 
如n=5时的方阵如下图所示: 
15 8 1 24 17
16 14 7 5 23
22 20 13 6 4
3 21 19 12 10
9 2 25 18 11
*/

#include <stdio.h>

int main() {
    int size = 0;

    printf("Input a Odd Num ");
    scanf("%d",&size);

    int num[size*size];
    int cube[size][size];

    for(int i = 0;i < size;i++) {
        for(int j = 0;j < size;j++) {
            cube[i][j] = 0;
        }
    }

    for(int i = 0, j = 1;i < size*size,j <= size*size;i++,j++) {
            num[i] = j;
    }

//算法区////////////////////////////////////////////////////////////////////////////

    int count = 0;
    int row = size / 2;
    int column = 0;
  
    while(count != size*size) {
        cube[column][row] = num[count];
        
        count++;
        column--;
        row--;
        
        if(row < 0) {
            row = size - 1;
        }
        if(column < 0) {
            column = size - 1;
        }

        //如果循环一斜完成，进入下一
        if(cube[column][row] != 0) {
            column += 2;
            row += 1;
            //越界
            if (column >= size) {
                column -= size;
            }
            if (row >= size) {
                row -= size;
            }
        }
    }

//算法区///////////////////////////////////////////////////////////////////

    printf("\n");
    for(int i = 0;i < size;i++) {
        for(int j = 0;j < size;j++) {
            printf("%d ",cube[i][j]);
        }
        printf("\n");
    }
}

