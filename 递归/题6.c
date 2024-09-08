#include <stdio.h>
#include <stdlib.h>

#define Nil -1
#define N 14

char list[N] = {
    NULL,'A','B','C','D','E','F',NULL,NULL,'G','H','I',NULL,'J'
};

void F(int i) {
    if(i <= N) {
        F(2*i);
        if(list[i]) printf("%c",list[i]);
        F(2*i+1);
    }
}

int main() {
    F(1);
}