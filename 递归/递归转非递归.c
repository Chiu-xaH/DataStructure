#include <stdio.h>

#define MAXSIZE 200
#define OK 1
#define ERROR 0

typedef int Status;
typedef int Elemtype;

typedef struct {
    int W;
    int state;  // 状态：0 表示需要处理第一次递归，1 表示需要处理第二次递归
} Frame;

typedef struct {
    int top;
    Frame data[MAXSIZE];
} Stack;


Status Init(Stack *S) {
    S->top = -1;
    return OK;
}
Status Push(Stack *S,Frame  E) {
    if(S->top == MAXSIZE) {
        return ERROR;
    }
    S->top++;
    S->data[S->top] = E;
    return OK;
}
Status Pop(Stack *S,Frame  *E) {
    if(S->top == -1) {
        return ERROR;
    }
    *E = S->data[S->top];
    S->top--;
    return OK;
}


void  P2(int N, int *F)
        { 
             if (N==0) 
                *F=0;
             else  {  P2(N-1, F); *F=*F+N;  } 
        } 
int  F(int N) 
        {
             if ( N==0)  return 0;
             else  if (N==1)
                            return 1;
                     else  return F(N-1)+2*F(N-2);
        } 

//递归
void PrintRV(int N) {
    if (N>0) {      
        printf("%d",N % 10);
        PrintRV(N / 10);
    } 
} 

//非递归
void PrintRVNot(int N) {
    while(N > 0) {
        printf("%d",N % 10);
        N /= 10;
    }
}

//递归
void PrintV(int N) {
    if (N>0) {   
        PrintV(N / 10);   
        printf("%d",N % 10);
    } 
}

//非递归
/*void PrintVNot(int N) {
    Stack S;
    Init(&S);
    while (N>0) {  
        Push(&S,N % 10); 
        N /= 10;   
    }
    while (S.top != -1) {
        Elemtype E;
        Pop(&S,&E);
        printf("%d",E);
    } 
}*/

void  PC(int M, int N, int *K )
      {
              if (N==0)  
                 *K = 1;
              else{
                         PC(M-1, N-1, K); 
                         *K=*K*M / N;  
              } 
      } 

      int   SS(int N)
     { 
            if (N==0 ) return 100;
            else  return SS(N-1)+N*N;
      } 
    
int main() {
   // printf("%d",F(5));
    //int M= 3;
   // P2(4,&M);
   // printf("%d",M);
 //  PrintRV(12345);
 //  PrintRVNot(12345);
//  int M; 
  //PC(6, 4, &M); 
  P(4);
  printf("\n");
  PNot2(4);
 // printf("%d",SS(5));
 //PrintVNot(12345);
}