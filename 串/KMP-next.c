#include<stdio.h>
#include<string.h>
//摘取自CSDN
int next[100];
void getnext(char s[],int length){
	next[0]=0;
	for(int i =1;i<length;i++){
		if(i==1){
			if (s[1]==s[0]) next[1]=1;
			else next[1]=0;
		}
		if(s[i]==s[next[i-1]]) next[i]=next[i-1]+1;
		else if (s[i]==s[0]) {
			next[i]=1;
		}
		else{
			next[i]=0;
		} 
	}
	for(int i =length-1;i>0;i--){
		next[i]=next[i-1]+1;
	}
}
int main(){
	char s[] = "ADABCADADA";
    getnext(s,10);
	for(int i =0;i<10;i++)
	printf("%d ",next[i]);
	
}
