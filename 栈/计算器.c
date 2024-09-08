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

//得到栈顶元素但不弹出
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
        //是数字
        if(!isSign(middle[ptr]) && middle[ptr] != ' ') {
            end[endPtr] = middle[ptr];
            endPtr++;
        }
        if(middle[ptr] == ' ') {
            end[endPtr] = ' ';
            endPtr++;
        }
        //左括号、乘除号直接入栈
        if(middle[ptr] == '(' || middle[ptr] == '*' || middle[ptr] == '/') {
            Push(&S,middle[ptr]);
        }
        //右括号出栈到左括号为止
        if(middle[ptr] == ')') {
            Elemtype E;
            while(Top(S) != '(') {
                Pop(&S,&E);
                end[endPtr] = E;
                endPtr++;
            }
            //出栈剩下的右括号
            Pop(&S,&E);
        }
        //加减号，比较栈顶是否为*/，是则全部出栈，再进栈加减号
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
            //这里已经得到数字，再定义一个新的INT栈，就可以算了，略
        }
    }
}

int main() {
    char middle[MAXSIZE];
    char end[MAXSIZE];
    printf("欢迎使用计算器 请输入中缀表达式(数需空格隔开,控制在100字符以内)\n");
    gets(middle);
    Transfer(middle,end);
    int i = 0;
    while(end[i] != '\0') {
        printf("%c",end[i]);
        i++;
    }
    Jisuan(end);
}
/*
int mains() {
    //定义中缀转后缀栈，后缀计算栈
    Stack transforStack,calculateStack;
    Status transferI,calculateI;

    char middle[MAXSIZE];
    char end[MAXSIZE];
    int left = INFINITY;
    printf("欢迎使用计算器 请输入中缀表达式(不要带空格,控制在100字符以内)\n");
    gets(middle);

    transferI = Init(&transforStack);
    int i = 0,j = 0;
    while(middle[i] != '\0') {
        if(middle[i] > '0' && middle[i] < '9') {
            //数字
            end[j] = middle[i];
            j++;
        } 
        if(
            middle[i] == '*' || 
            middle[i] == '/' || 
            middle[i] == '+' || 
            middle[i] == '-' || 
            middle[i] == '(' || 
            middle[i] == ')'
            ) {
                char e = Top(&transforStack);
                if(e != NULLS) {
                    char tops = Top(&transforStack);
                    if(middle[i] == ')') {
                        if(left != INFINITY) {
                            //()中间出栈
                            while(transforStack.top > left) {
                               // printf("%d",transforStack.top);
                                Elemtype e;
                                transferI = Pop(&transforStack,&e);
                                end[j] = e;
                                j++;
                            }
                            transferI = Pop(&transforStack,&e);
                            //删除出栈的）字符
                           // end[j-1] = '\0';
                        } else {
                            printf("输入的表达式不对！");
                            break;
                        }
                    } else 
                    if(middle[i] == '(') {
                        transferI = Push(&transforStack,middle[i]);
                        left = transforStack.top;
                    } else 
                    if(middle[i] == '+' || middle[i] == '-') {
                        if(tops == '*' || tops == '/') {
                            //出栈后
                            while (transforStack.top != -1) {
                                Elemtype e;
                                transferI = Pop(&transforStack,&e);
                                end[j] = e;
                                j++;
                            }
                            //再进栈
                            transferI = Push(&transforStack,middle[i]);
                        } else {
                            transferI = Push(&transforStack,middle[i]);
                        }
                    } else 
                    if(middle[i] == '*' || middle[i] == '/') {
                        transferI = Push(&transforStack,middle[i]);
                    }
                } else {
                    transferI = Push(&transforStack,middle[i]);
                }
        }
        i++;
    }
    end[j] = transforStack.data[transforStack.top] ;
    end[j+1] = '\0';

    printf("%s\n",end);




    calculateI = Init(&calculateStack);
    int result = 0;
    int k = 0,l = 0;
    while(end[k] != '\0') {
        if(isdigit(end[k]) != 0) {
            //数字
            calculateI = Push(&calculateStack,end[k]);
        } 
        if(
            end[k]  == '*' || 
            end[k]  == '/' || 
            end[k]  == '+' || 
            end[k]  == '-'
            ) {
                Elemtype num2,num1;
                int new = 0;
                calculateI = Pop(&calculateStack,&num2);
                calculateI = Pop(&calculateStack,&num1);
                int num22  = transfer(num2);
                int num11 = transfer(num1);
                if(end[k]  == '*') {
                    new  = num11 * num22 ;
                } else if(end[k] == '/') {
                    new = num11 / num22;
                } else if(end[k] == '+') {
                    new = num11 + num22;
                } else if(end[k] == '-') {
                    new = num11 - num22;
                }
                result = new;
                Elemtype num3 = transfer2(new);
                calculateI = Push(&calculateStack,num3);
            }
        calculateI = Get(&calculateStack);  
        k++;
    }
    if (calculateStack.top == 1) {
        result += transfer(calculateStack.data[0]);
    }

    
    printf("结果为 %d",result);
    return 0;
}

*/