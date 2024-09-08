#include <iostream>
using namespace std;

void  P1(int W)
       {     int A,B;  
             A=W-1;  B=W+1;
             cout<<A<<B;
        } 
    
       void  P2(int W ) {     
        int A,B;  
             A=2*W;  B=W*W;
             P1(A);  P1(B);
             cout<<A<<B;
       } 
void  P(int W)
        { 
               if (W>0)


               {
                cout<<W;
                     P(W-1);
                   cout<<W;   
                } 
        } 

        void  P4(int W)
        {
               if (W>0)
               {    P(W-1);
                     P(W-1);
                     cout<<W;
               } 
         } 

int  Hcf2(int M, int N)
        {    int H;
              while (N!=0)
              {  
                    H=M % N;
                    M=N; N=H;
               } 
               cout<<M;  return M;
        } 

 int Hcf(int M, int N)
        {      int H;
               while (N!=0)
                {  
                    H = M % N;
                    M = N; N = H;
                } 
                return M;
        } 
        //化简
        void  Reduce(int M1, int N1, int *M2, int *N2)
        {     int R;
              R=Hcf(M1, N1);
              * M2 = M1 / R;  * N2 = N1 / R;
              cout<< M1 <<'/'<< N1 <<'='<<* M2 <<'/'<<*N2;
        } 
int main() {
  //  int X,Y,M,N;
 //Reduce(100,200, &X, &Y);
         //      Reduce(300,550, &M, &N);
         P(4);
    return 0;
}