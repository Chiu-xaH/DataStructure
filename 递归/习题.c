#include <stdio.h>

void P1(int W) {
    int A,B;
    A = W-1;
    B = W+1;
    printf("%d%d",A,B);
}

void P2(int W) {
    int A,B;
    A = 2*W;
    B = W*W;
    P1(A);
    P1(B);
    printf("%d%d",A,B);
}

int Hcf(int M,int N) {
    int H;
    while(N != 0) {
        H = M % N;
        M = N;
        N = H;
    }
    //printf("%d",M);
    return M;
}

void reduce(int M1,int N1,int *M2,int *N2) {
    int R,J;
    R = Hcf(M1,N1);
    *M2 = M1/R;
    *N2 = N1/R;
    printf("%d/%d=%d/%d",M1,N1,*M2,*N2);
}

void P(int W) {
    if(W > 0) {
        printf("%d",W);
        P(W-1);
        printf("%d",W);
    }
}
 
void PP(int N,int *F) {
    if(N == 0) {
        *F = 0;
    } else {
        PP(N-1,F);
        *F += N;
    }
}

void PrintRV(int N) {
    if(N > 0) {
        printf("%d",N % 10);
        PrintRV(N / 10);
    }
}

void PC(int M,int N,int *K) {
    if(N == 0) {
        *K = 1;
    } else {
        PC(M-1,N-1,K);
        *K = *K * M / N;
    }
}

int SS(int N) {
    if(N == 0) {
        return 100;
    } else {
        return SS(N-1) + N*N;
    }
}

int ACM(int M,int N) {
    if(M == 0) {
        return N+1;
    } else if(N == 0) {
        return ACM(M-1,1);
    } else {
        return ACM(M-1,ACM(M,N-1));
    }
}

void PPP(int N) {
    if(N > 0) {
        PPP(N-1);
        printf("%d",N);
        PPP(N-1);
    }
}



int main() {
    //P2(5);
    //printf("%d",Hcf(100,350));
    //printf("\n%d",Hcf(200,49));
    //int X,Y,M,N,F;
    //reduce(100,200,&X,&Y);
    //reduce(300,500,&M,&N);
    //PP(4,&F);
    //printf("%d",F);
    //PrintRV(12345);
    //PC(10,4,&M);
    //printf("%d",M);
    //printf("%d",SS(5));
    //printf("%d",ACM(2,0));
    PPP(3);
}