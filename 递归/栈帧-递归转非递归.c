#include <stdio.h>

#define MAXSIZE 1000

typedef struct {
    int m;
    int n;
    int state;  
    // 状态：0 表示还未计算，
    //1 表示已经处理过 m-1 的计算
} Frame;

typedef struct {
    int top;
    Frame data[MAXSIZE];
} Stack;

void Init(Stack *S) {
    S->top = -1;
}

int Push(Stack *S, Frame frame) {
    if (S->top == MAXSIZE - 1) {
        return 0;  // 栈满
    }
    S->top++;
    S->data[S->top] = frame;
    return 1;
}

int Pop(Stack *S, Frame *frame) {
    if (S->top == -1) {
        return 0;  // 栈空
    }
    *frame = S->data[S->top];
    S->top--;
    return 1;
}

int f(int N) {
    if(N == 0) {
        return 0;
    } else if(N == 1) {
        return 1;
    } else {
        return f(1) + f(2);
    }
}
//递归函数
int Ack(int m,int n) {
    if(m == 0) { 
        return n+1;
    }
    if(n == 0) {
        return Ack(m-1,1);
    }
    if(m > 0 && n > 0) {
        return Ack(m-1,Ack(m,n-1));
    }
}
/*
Ack(0, n) = n + 1
Ack(m, 0) = Ack(m-1, 1)
Ack(m, n) = Ack(m-1, Ack(m, n-1))
*/
int AckRecursion(int m,int n) {
    Stack S;
    Init(&S);
    Frame curretFrame = { m,n,0 };
    Push(&S,curretFrame);

    while(S.top != -1) {
        Pop(&S,&curretFrame);
        
        if(curretFrame.m == 0) { 
            n = curretFrame.n + 1;
        } else if(curretFrame.n == 0) {
            curretFrame.m -= 1;
            curretFrame.n = 1;
            //Ack(m-1, 1)递归
            Push(&S,curretFrame);
            continue;
        } else if(curretFrame.state == 0) {
            /// 新n = Ack(m, n-1)
            //处理第一次递归
            curretFrame.state = 1;
            Push(&S,curretFrame);
            Frame newFrame = {curretFrame.m, curretFrame.n - 1, 0};
            Push(&S,newFrame);
            continue;
        } else if(curretFrame.state == 1) {
            //Ack(m, n) = Ack(m-1, 新n)
            //处理第二次递归
            n = curretFrame.n;
            curretFrame.m -= 1;
            Push(&S,curretFrame);
            continue;
        }
    }
    return n;
}
//非递归函数
void PP2(int N) {
    if(N > 0) {
        PP(N-1);
        printf("%d",N);
        PP(N-1);
    }
}

void  P(int W) { 
    if (W>0){
        printf("%d",W);
        P(W-1);
        printf("%d",W);
    } 
}

void PRecursion(int W) {
    Stack S;
    Init(&S);
    Frame curretFrame = { W,0,0 };
    Push(&S,curretFrame);
    while(S.top != -1) {
        Pop(&S,&curretFrame);
        if (curretFrame.m > 0) {
            if (curretFrame.state == 0) {
                // 第一次打印
                printf("%d", curretFrame.m);

                // 准备递归
                curretFrame.state = 1;
                Push(&S, curretFrame);

                // 递归到 W-1
                Frame newFrame = {curretFrame.m - 1,0, 0};
                Push(&S, newFrame);
            } else if (curretFrame.state == 1) {
                // 第二次打印
                printf("%d", curretFrame.m);
            }
        }
    }
}

void  PrintV(int N) {
    if (N>0) {  
        PrintV(N / 10);
        printf("%d",N % 10);                  
    } 
} 

void PrintVRecursion(int N) {
    Stack S;
    Init(&S);
    Frame curretFrame = { N,0,0 };
    Push(&S,curretFrame);
    while(S.top != -1) {
        Pop(&S,&curretFrame);
        if(curretFrame.m > 0) {
            if(curretFrame.state == 0) {
                  // 准备递归
                curretFrame.state = 1;
                Push(&S, curretFrame);

                // 递归到 W-1
                Frame newFrame = {curretFrame.m / 10,0, 0};
                Push(&S, newFrame);
            } else if(curretFrame.state == 1) {
                // 第二次打印
                printf("%d", curretFrame.m % 10);
            }
        }
    }
}

void  PrintRV(int N) {
    if (N>0) {
        printf("%d",N % 10); 
        PrintRV(N / 10);
    } 
} 

void PrintRVRecursion(int N) {
    Stack S;
    Init(&S);
    Frame curretFrame = { N,0,0 };
    Push(&S,curretFrame);
    while(S.top != -1) {
        Pop(&S,&curretFrame);
        if(curretFrame.m > 0) {
            if(curretFrame.state == 0) {
                // 第二次打印
                // 准备递归
                curretFrame.state = 1;
                Push(&S, curretFrame);
                printf("%d", curretFrame.m % 10);
            } else if(curretFrame.state == 1) {
                // 递归到 W-1
                Frame newFrame = {curretFrame.m / 10,0, 0};
                Push(&S, newFrame);
            }
        }
    }
}
//递归
void PP(int W) {
    if(W > 0) {
        PP(W-1);
        PP(W-1);
        printf("%d",W);
    }
}

void PPRecursion(int W) {
    Stack S;
    Frame curretFrame = {W,0,0};
    Init(&S);

    Push(&S,curretFrame);
    while(S.top != -1) {
        Pop(&S,&curretFrame);
        if(curretFrame.m > 0) {
            if(curretFrame.state == 0) {
                // 处理第1个递归调用
                curretFrame.state = 1;
                Push(&S,curretFrame);


                Frame newFrame = {curretFrame.m - 1,0,0};
                Push(&S,newFrame);
            } else if(curretFrame.state == 1) {
                 // 处理第2个递归调用
                 curretFrame.state = 2;
                 Push(&S,curretFrame);

                 Frame newFrame = {curretFrame.m - 1,0,0};
                 Push(&S,newFrame);
            } else {
                //打印
                printf("%d",curretFrame.m);
            }
        }
    }
}

int main() {
    //printf("%d",Ack(3,8));
   // printf("\n");
   // printf("%d",AckRecursion(3,8));
  //  P(6);
   // printf("\n");
   // PRecursion(6);
   //PrintRV(12345);
  // printf("\n");
  // PrintRVRecursion(12345);
   //P(4);
   printf("\n");
   PRecursion(4);
    return 0;
}