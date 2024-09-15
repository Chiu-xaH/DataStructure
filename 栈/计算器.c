#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define NULLS 0

typedef int Status;
typedef char Elemtype;
typedef struct {
    int top;
    Elemtype data[MAXSIZE];
} Stack;

Status Init(Stack *S) {
    S->top = -1;
    return OK;
}

Status Push(Stack *S,Elemtype E) {
    if(S->top == MAXSIZE) {
        return ERROR;
    }
    S->top++;
    S->data[S->top] = E;
    return OK;
}

Status Pop(Stack *S,Elemtype *E) {
    if(S->top == -1) {
        return ERROR;
    }
    *E = S->data[S->top];
    S->top--;
    return OK;
}

Status Get(Stack *S) {
    if(S->top == -1) {
        return ERROR;
    }
   
    for(int i = S->top;i > -1;i--) {
        printf("%c ",S->data[i]);
    }
    printf("]\n");
    return OK;
}

//�õ�ջ��Ԫ�ص�������
Elemtype Top(Stack S) {
    if(S.top == -1) {
        return NULLS;
    }
    return S.data[S.top];
}

int transfer(char str) {
    if(str == '0') {
        return 0;
    } else if(str == '1') {
        return 1;
    } else if(str == '2') {
        return 2;
    } else if(str == '3') {
        return 3;
    } else if(str == '4') {
        return 4;
    } else if(str == '5') {
        return 5;
    } else if(str == '6') {
        return 6;
    } else if(str == '7') {
        return 7;
    } else if(str == '8') {
        return 8;
    } else if(str == '9') {
        return 9;
    } else return 0;
}

char transfer2(int str) {
    if(str == 0) {
        return '0';
    } else if(str == 1) {
        return '1';
    } else if(str == 2) {
        return '2';
    } else if(str == 3) {
        return '3';
    } else if(str == 4) {
        return '4';
    } else if(str == 5) {
        return '5';
    } else if(str == 6) {
        return '6';
    } else if(str == 7) {
        return '7';
    } else if(str == 8) {
        return '8';
    } else if(str == 9) {
        return '9';
    } else return '0';
}


Status isSign(char str) {
    if(
        str == '(' || str == ')'||
        str == '+' || str == '-'||
        str == '*' || str == '/'
        ) return OK;
    return ERROR;
}

void Transfer(char middle[],char end[]) {
    Stack S;
    Init(&S);
    int ptr = 0,endPtr = 0;

    while(middle[ptr] != '\0') {
        //������
        if(!isSign(middle[ptr]) && middle[ptr] != ' ') {
            end[endPtr] = middle[ptr];
            endPtr++;
        }
        if(middle[ptr] == ' ') {
            end[endPtr] = ' ';
            endPtr++;
        }
        //�����š��˳���ֱ����ջ
        if(middle[ptr] == '(' || middle[ptr] == '*' || middle[ptr] == '/') {
            Push(&S,middle[ptr]);
        }
        //�����ų�ջ��������Ϊֹ
        if(middle[ptr] == ')') {
            Elemtype E;
            while(Top(S) != '(') {
                Pop(&S,&E);
                end[endPtr] = E;
                endPtr++;
            }
            //��ջʣ�µ�������
            Pop(&S,&E);
        }
        //�Ӽ��ţ��Ƚ�ջ���Ƿ�Ϊ*/������ȫ����ջ���ٽ�ջ�Ӽ���
        if(middle[ptr] == '+' || ptr[middle] == '-' ) {
            if(Top(S) == '*' || Top(S) == '/') {
                Elemtype E;
                while(S.top != -1) {
                    Pop(&S,&E);
                    end[endPtr] = E;
                    endPtr++;
                }
            }
            Push(&S,middle[ptr]);
        }
        ptr++;
    }
    while(S.top != -1) {
        Elemtype E;
        Pop(&S,&E);
        end[endPtr] = E;
        endPtr++;
    }
    end[endPtr] = '\0';
}

void Jisuan(char end[]) {
    Stack S;
    Init(&S);
    int ptr = 0;
    while(end[ptr] != '\0') {
        if(end[ptr] == ' ') {
            ptr++;
            continue;
        }
        if(isdigit(end[ptr])) {
            int num = 0;
            while(isdigit(end[ptr])) {
                num = num*10 + (end[ptr] - '0');
                ptr++;
            }
            //�����Ѿ��õ����֣��ٶ���һ���µ�INTջ���Ϳ������ˣ���
        }
    }
}

int main() {
    char middle[MAXSIZE];
    char end[MAXSIZE];
    printf("��ӭʹ�ü����� ��������׺���ʽ(����ո����,������100�ַ�����)\n");
    gets(middle);
    Transfer(middle,end);
    int i = 0;
    while(end[i] != '\0') {
        printf("%c",end[i]);
        i++;
    }
    Jisuan(end);
}