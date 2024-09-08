#include <stdio.h>

int main() {
    char ch;
    FILE *fp = fopen("1.txt","r");
    //读取文件
    char a[100];int i = 0;
    ch = getc(fp);
    while(ch != EOF) {
    //  putchar(ch);  
       a[i] = ch;
        i++;
        ch = getc(fp);
    }
    //写入文件
   // while((ch = getchar()) != '#')
    //putc(getchar(),fp);
    fclose(fp);
    fp = fopen("2.txt","w");
    while(i >= 0) {
        putc(a[i],fp);
        i--;
    }
}
//将一个磁盘文件中的内容复制到另一个文件中
//从文件中输入字符串，并打印其内容
//从f1.txt中读字符串和一个十进制数，输出到显示器
//从文件中读入学生信息数据，计算总分、平均分并按总分排序后写入另一个文件
//输入数据存入文件显示并查找