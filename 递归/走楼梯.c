#include <stdio.h>

int Step(int n) {
    if(n == 1) {
        return 1;
    }
    if(n == 2) {
        return 2;
    }
    return Step(n-1) + Step(n-2);
}
int main() {
    //int n =;
    printf("%d",Step(8));
    return 0;
}