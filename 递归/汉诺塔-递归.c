//汉诺塔 递归思想
#include<stdio.h>
#include<math.h>
int Hanoi_count(int n) {
	return pow(2, n) - 1;
}
void move(int x, int y) {
	printf("%c->%c\n", x, y);
}
void Hanoi(int n, char a, char b, char c) {
	if (n == 1) {
		move(a, c);
	} else {
		Hanoi(n - 1, a, c, b);//将A座上的n-1个盘子借助C座移向B座
		move(a, c);//将A座上最后一个盘子移向C座
		Hanoi(n - 1, b, a, c);//将B座上的n-1个盘子借助A座移向C座
	}
}
//move中的实参与hanoi函数中的形参相对应，而hanoi函数中形参a，b，c所对应的值也是在有规律的变化
int main() {
	int n = 0;
	scanf("%d", &n);
	int ret = Hanoi_count(n);
	printf("%d Hannuo %d Steps\n", n, ret);
	Hanoi(n, 'A', 'B', 'C');
	return 0;
}
