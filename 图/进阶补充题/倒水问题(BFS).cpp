#include <iostream>
#include <queue>
#define MAX 100
using namespace std;
/*
倒水问题：
给定 2 个没有刻度容器，对于任意给定的容积，求出如何只用两个瓶装出 L 升的水，如果可以，输出步骤，如果不可以，请输出 No Solution
*/
struct Pool {
    //两个杯子的容量和水
    int x,y,l;
    string s;
} current;

queue<Pool> Queue;
bool visited[MAX][MAX];

void init(int L) {
    for(int i = 0;i < L;i++) {
        for(int j = 0;j < L;j++) {
            visited[i][j] = false;
        }
    }
}
//BFS 
/*倒水无非8种操作：
1 把X装满
2 把Y装满
3 把X倒空
4 把Y倒空
5 X向Y中倒水，X倒完，Y没有被装满
6 X向Y中倒水，Y被装满
7 Y向X中倒水，Y倒完，X没有被装满
8 Y向X中倒水，X被装满。
*/
string BFS(int maxX, int maxY, int target) {
    Pool current;
    current.x = 0;
    current.y = 0;
    current.l = target;
    current.s = "";
    //入队
    Queue.push(current);
    visited[current.x][current.y] = true;

    while (!Queue.empty()) {
        //出队
        Pool current = Queue.front();
        Queue.pop();

        // 如果找到目标水量
        if (current.x == current.l || current.y == current.l)
            return current.s;

        // 1. 把X装满
        if (!visited[maxX][current.y]) {
            Pool next = current;
            next.x = maxX;
            next.s += "把X装满\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 2. 把Y装满
        if (!visited[current.x][maxY]) {
            Pool next = current;
            next.y = maxY;
            next.s += "把Y装满\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 3. 把X倒空
        if (!visited[0][current.y]) {
            Pool next = current;
            next.x = 0;
            next.s += "把X倒空\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 4. 把Y倒空
        if (!visited[current.x][0]) {
            Pool next = current;
            next.y = 0;
            next.s += "把Y倒空\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 5. 把X中的水倒入Y中，X倒完，Y没有装满
        if (current.x + current.y <= maxY && !visited[0][current.x + current.y]) {
            Pool next = current;
            next.y = current.x + current.y;
            next.x = 0;
            next.s += "把X中的水倒入Y中,X倒完,Y没有装满\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 6. 把X倒入Y中，Y被装满
        if (current.x + current.y > maxY && !visited[current.x + current.y - maxY][maxY]) {
            Pool next = current;
            next.x = current.x + current.y - maxY;
            next.y = maxY;
            next.s += "把X倒入Y中,Y被装满\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 7. 把Y中的水倒入X中，Y倒完，X没有装满
        if (current.x + current.y <= maxX && !visited[current.x + current.y][0]) {
            Pool next = current;
            next.x = current.x + current.y;
            next.y = 0;
            next.s += "把Y中的水倒入X中,Y倒完,X没有装满\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 8. 把Y倒入X中，X被装满
        if (current.x + current.y > maxX && !visited[maxX][current.y + current.x - maxX]) {
            Pool next = current;
            next.y = current.x + current.y - maxX;
            next.x = maxX;
            next.s += "把Y倒入X中,X被装满\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }
    }

    return "无解";
}

int main() {
    int x, y, l;
    cout << "输入两个杯子容量X、Y和水总量L\n";
    cin >> x >> y >> l;
    init(l);  // 初始化访问标记数组
    string result = BFS(x,y,l);
    cout << result << endl;
}
