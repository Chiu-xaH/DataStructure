

#include <stdio.h>



int F(int N) {
    if ( N<=2)  return 1;
    return (2*F(N-1)+3*F(N-2)); 
}



int main() {
    int i = F(6);
    printf("%d",i);
}