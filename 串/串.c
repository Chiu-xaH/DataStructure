#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int Status;
typedef char String[MAXSIZE+1]; /*  0号单元存放串的长度 */

Status Init(String S) {
    if(MAXSIZE == 0) {
        return ERROR;
    }
    S[0] = 0;
    return OK;
}

Status Assign(String S,char *ch) {
    if(strlen(ch) > MAXSIZE) {
        return ERROR;
    }
    S[0] = strlen(ch);
    for(int i = 0;i < strlen(ch);i++) {
        S[i+1] = ch[i];
    }
    return OK;
}

int Length(String S) {
    return S[0];
}

//对比字符串是否相等，是则返回OK，反之ERROR
Status Equal(String S1,String S2) {
    int lengthS1 = Length(S1),lengthS2 = Length(S2);
    int count = 0;
    if(lengthS1 != lengthS2) {
        return ERROR;
    } else {
        //长度相等
        for(int i = 1;i <= lengthS1;i++) {
            if(S1[i] == S2[i]) {
                count++;
            }
        }
        if(count == lengthS1) {
            return OK;
        } else {
            return ERROR;
        }
    }
}

Status Delete(String S,int i) {
    int len = Length(S);
    if(i > Length(S)) {
        return ERROR;
    }
    S[0] = i -1;
    for(int k = i+1;k <= len;k++) {
        S[k] = '\0';
    }
    return OK;
}

//将S2连接到S1
Status Link(String S1,String S2) {
    int lengthS1 = Length(S1),lengthS2 = Length(S2);
    
    for (int i = 1; i <= lengthS2; i++) {
        S1[lengthS1 + i] = S2[i];
    }
    S1[0] =lengthS1 + lengthS2;
    return OK;
}

Status Sub(String S,int i,int j,String NewS) {
    if(j <= i) {
        return ERROR;
    }
    if(j > Length(S)) {
        return ERROR;
    }
    NewS[0] = j - i;
    for(int z = i+1,k = 1;z <= j;z++,k++) {
        NewS[k]=S[z];
    }
    return OK;
} 

Status Get(String S) {
    if(Length(S) == 0) {
        return ERROR;
    }
    for(int i = 1;i <= Length(S);i++) {
        printf("%c",S[i]);
    }
    printf("\n");
    return OK;
}

//[S1HOU][S2]
//[S1QIAN]
//插入S2到S1的第place个字符
Status Insert(String S1,String S2,int place) {
    String NewS;
    Init(NewS);

    Sub(S1,place,Length(S1),NewS);
    Link(S2,NewS);
    Delete  (S1,place+1);
    Link(S1,S2);

    return OK;
}
//搜索子串S1在串S中是否出现，
//若出现，以子串S1的首字符在S中的位置作为结果返回，
//否则返回0；
Status Search(String S,String Son) {
    int i = 1,j = 1;
    while(i <= S[0] && j <= Son[0]) {
        if(S[i] == Son[j]) {
            i++;
            j++;
        } else {
            i = i-j+2;
            j = 1;
        }
    }
    if(j > Son[0]) {
        return i-Son[0];
    } else return -1;
}

//用字串S1替换串S中从第i个字符开始的len个字符。
Status Replace(String S,String Son,String ReplaceStr) {
    int i = 1;
    while(i <= S[0]) {
        // 取出长度为T[0]的子串Sub
        //if (strcmp(sub + 1, T + 1) == 0) {  // 如果子串和T匹配
        //StrDelete(S, i, T[0]);  // 删除子串T
        ///StrInsert(S, i, V);  // 插入子串V
        //i += V[0];  // 更新i的位置
//else i++;
    }
}



int main() {
    String S,S2,S3,S4;
    Status i;
    char ch;
    i = Init(S);
    i = Init(S2);
    i = Init(S3);
     i = Init(S4);
    i = Assign(S,"abcde");
    i = Assign(S2,"cd");
    i = Assign(S4,"Z");
 //   i = Get(S);
 //   i = Equal(S,S2);
 //   if(i){
 //       printf("YES");
 //   } else printf("NO");
    //i = Link(S,S2);
    //i = Get(S);
 //   i = Sub(S,0,4,S3);
    //printf("%d",i);
    //i = Get(S4);
    //i = Insert(S,S4,2);

   /// i = Delete(S3,2);
//    i = Get(S);
    i = Search(S,S2);
    if(i != 0) {
        printf("YES %d",i);
    } else {
        printf("NO");
    }
    return 0;
}