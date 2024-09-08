//栈
#include "Stack.h"
//设计算法对以字符串形式读入的表达式S，判断其中的各括号(){}[]是否匹配
Status isMatch(char left,char right) {
    if(left == '(' && right == ')') {
        return OK;
    }
    if(left == '[' && right == ']') {
        return OK;
    }
    if(left == '{' && right == '}') {
        return OK;
    }
    return ERROR;
}

Status isSuited(char str[]) {
    Stack S;
    InitStack(&S);
    int ptr = 0;
    Elemtype Top;
    while(str[ptr] != '\0') {
        if(
        str[ptr] == '(' || 
        str[ptr] == '[' || 
        str[ptr] == '{' 
       ) {
            Push(&S,str[ptr]);
        } else if( 
        str[ptr] == ')' || 
        str[ptr] == ']' || 
        str[ptr] == '}') {
            if(Pop(&S,&Top) == ERROR || isMatch(Top,str[ptr]) == ERROR) {
                return ERROR;
            }
        }
        ptr++;
    }
    if(S.top == -1) {
        return OK;
    } else {
        return ERROR;
    } 
}


int main() {
    Status i;
   // Elemtype e = 9;
   // Stack S;
   // i = InitStack(&S);
   // i = Push(&S,1);
   // i = Push(&S,2);
   // i = Push(&S,3);
   // i = Pop(&S,&e);
   // i = Pop(&S,&e);

   // i = GetStack(S);
   i = isSuited("{[()}");
   if(i) {
    printf("YES");
   } else{
    printf("NO");
   }
}