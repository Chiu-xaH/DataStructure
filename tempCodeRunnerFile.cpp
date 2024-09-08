#include <iostream>
using namespace std;

int main() {
    int *p,*q;
    p = new int;
    q = new int;
    *p = 10;
    *q = 20;
    cout<<*p<<"-"<<*q<<endl;
    *p =*q;
    *q = 30;
    cout<<*p<<"-"<<*q<<endl;
    p = q;
    *p =40;
    *q = 50;
    cout<<*p<<"-"<<*q<<endl;
    return 0;
}