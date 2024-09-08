/*背包问题：设有n个物品，其重量分别为w1，w2，w3，…，wn，
所有物品的重量之和≥背包所能放置的重量S。
设计算法从中找出若干物品放入背包中，使得其重量之和正好为S 。 
例如，S = 50, n = 10,  w = ( 29  26  18  16  13  10  8  5  3  1)
(其中每一行为一个解。每一对数中，第一个为该元素在w中的序号，  第二个为元素的值）：
答案
  (1,29)  (3,18)  (9,3)       
  (1,29)  (4,16)  (8,5)                   
  (1,29)  (5,13)  (7,8)                        
  (1,29)  (5,13)  (8,5)   (9,3)    
  (1,29)  (6,10)  (7,8)   (9,3)               
  (2,26)  (3,18)  (8,5)   (10,1)  
  (2,26)  (4,16)  (7,8)                   
  (2,26)  (4,16)  (8,5)   (9,3)  
  (2,26)  (5,13)  (6,10)  (10,1) 
  (2,26)  (5,13)  (7,8)   (9,3)  
  (2,26)  (6,10)  (7,8)   (8,5)   (10,1)  
  (3,18)  (4,16)  (5,13)  (9,3)  
  (3,18)  (4,16)  (6,10)  (8,5)   (10,1)  
  (3,18)  (4,16)  (7,8)   (8,5)   (9,3)  
  (3,18)  (5,13)  (6,10)  (7,8)   (10,1)  
  (3,18)  (5,13)  (6,10)  (8,5)   (9,3)    (10,1)  
  (4,16)  (5,13)  (6,10)  (7,8)   (9,3)
*/
#include <stdio.h>

#define S 50
#define N 10

void findCombinations(const int w[], int start, int currWeight, int currCombination[], int index) {
    if (currWeight == S) {
        // 打印当前组合
        for (int i = 0; i < index; i++) {
            printf("(%d,%d) ", currCombination[i] + 1, w[currCombination[i]]);
        }
        printf("\n");
        return;
    }
    
    if (currWeight > S || start == N) {
        return;
    }

    // 选择当前物品
    currCombination[index] = start;
    findCombinations(w, start + 1, currWeight + w[start], currCombination, index + 1);

    // 不选择当前物品
    findCombinations(w, start + 1, currWeight, currCombination, index);
}

void doing() {
    const int w[N] = {29, 26, 18, 16, 13, 10, 8, 5, 3, 1};
    int currCombination[N];
    findCombinations(w, 0, 0, currCombination, 0);
}

int main() {
    doing();
    return 0;
}
