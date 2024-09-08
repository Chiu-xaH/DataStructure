#include <stdio.h>
//辗转相除法
//不断用较大的数除以较小的数并取余，直到余数为0，最后的除数即为最大公约数

//50 % 15 = 3（第一余数）
//15 % 3 = 0
//结果为
int MaxPublic(int A,int B) {
    if(A % B == 0) {
        return B;
    } else {
        return MaxPublic(B,A % B);
    }
}

int main() {
    printf("%d",MaxPublic(50,15));
    return 0;
}