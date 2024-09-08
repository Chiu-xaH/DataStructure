#include <stdio.h>

#define MAXSIZE 1000
#define OK 1
#define ERROR 0

typedef int Status;
typedef struct {
    int W;
    int state;
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

Status isEmpty(Stack S) {
    if(S.top == -1) {
        return OK;
    } else return ERROR;
}

void P(int W) { 
    if (W>0){
        printf("%d",W);
        P(W-1);
        printf("%d",W);
    } 
}

void PRecursion(int W) {
    Stack S;
    Init(&S);
    Frame frame;
    frame.state = 0;
    frame.W = W;
    Push(&S,frame);

    while(!isEmpty(S)) {
        Pop(&S,&frame);
        if(frame.W > 0) {
            if(frame.state == 0) {
                printf("%d",frame.W);
                //修改出栈的这个状态，然后再压回去
                frame.state = 1;
                Push(&S,frame);
                //递归
                Frame newFrame;
                newFrame.state = 0;
                newFrame.W = frame.W-1;
                Push(&S,newFrame);
            } else if(frame.state == 1) {
                printf("%d",frame.W);
            }
        } 
    }
}

void PrintV(int N) {
    if (N>0) {  
        PrintV(N / 10);
        printf("%d",N % 10);                  
    } 
} 

void PrintVRecursion(int W) {
    Stack S;
    Init(&S);
    Frame frame;
    frame.state = 0;
    frame.W = W;
    Push(&S,frame);
    while(!isEmpty(S)) {
        Pop(&S,&frame);
        if(frame.W > 0) {
            if(frame.state == 0) {
                frame.state = 1;
                Push(&S,frame);

                Frame new;
                new.state = 0;
                new.W = frame.W / 10;
                Push(&S,new);
            } else if(frame.state == 1) {
                printf("%d",frame.W % 10);
            }
        }
    }
}

void PrintRV(int N) {
    if (N>0) {
        printf("%d",N % 10); 
        PrintRV(N / 10);
    } 
} 

void PrintRVRecursion(int W) {
    Stack S;
    Init(&S);
    Frame frame;
    frame.state = 0;
    frame.W = W;
    Push(&S,frame);
    while(!isEmpty(S)) {
        Pop(&S,&frame);
        if(frame.W > 0) {
            if(frame.state == 0) {
                printf("%d",frame.W % 10);

                frame.state = 1;
                Push(&S,frame);

                Frame new;
                new.state = 0;
                new.W = frame.W / 10;
                Push(&S,new);
            } else if(frame.state == 1) {

            }
        }
    }
}

void PP(int W) {
    if(W > 0) {
        PP(W-1);
        PP(W-1);
        printf("%d",W);
    }
}

void PPRecursion(int W) {
    Stack S;
    Init(&S);
    Frame frame;
    frame.state = 0;
    frame.W = W;
    Push(&S,frame);
    while(!isEmpty(S)) {
        Pop(&S,&frame);
        if(frame.W > 0) {
            if(frame.state == 0) {
                frame.state = 1;
                Push(&S,frame);

                Frame new;
                new.state = 0;
                new.W = frame.W - 1;
                Push(&S,new);
            } else if(frame.state == 1) {
                frame.state = 2;
                Push(&S,frame);

                Frame new;
                new.state = 0;
                new.W = frame.W - 1;
                Push(&S,new);
            } else if(frame.state == 2) {
                printf("%d",frame.W);
            }
        }
    }
}



int main() {
    PP(3);
}