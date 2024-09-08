#include <stdio.h>
int n = 15;
char A[] = { ' ','A','B','C','D','E','F','G','O','O','H','O','I','J','K','L'};
void P(int i) {
    if(i <= n && A[i] != 'O') {
        P(2*i);
        printf("%c",A[i]);
        P(2*i+1);
    }
}
int main() {
    P(1);
}