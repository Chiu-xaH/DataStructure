#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define SIZE 120
#define NULLKEY -32768

typedef int Status;

typedef struct {
    int *elem;//动态分配数组
    int count;
} Hash;

Status Init(Hash *H) {
    H->count = SIZE;
    H->elem = (int *)malloc(H->count * sizeof(int));
    for(int i = 0;i < H->count;i++) {
        H->elem[i] = NULLKEY;
    }
    return OK;
}

int Length(Hash H) {
    return H.count;
}

int HashFun(int key,Hash H) {
    return key % 13;
}

void Insert(Hash *H,int key) {
    int address = HashFun(key,*H);
    //线性探测法解决冲突，寻找空位
    while(H->elem[address] != NULLKEY) {
        address = (address+1) % Length(*H);
    }
    H->elem[address] = key;
}

void Get(Hash H) {
    int length = H.count;
    for(int i = 0;i < length;i++) {
        if(H.elem[i] != NULLKEY)
        printf("%d ",H.elem[i]);
    }
    printf("\n");
}

Status Search(Hash H,int key) {
    int address = HashFun(key,H);
    while(H.elem[address] != key) {
        address = (address+1) % Length(H);
        //循环到底或循环到源点
        if(H.elem[address] == NULLKEY || address == HashFun(key,H)) {
            return ERROR;
        }
    }
    return OK;
}
//得到查找长度
int SearchLength(Hash H,int key) {
    int address = HashFun(key,H);
    int count = 1;
    while(H.elem[address] != key) {
        address = (address+1) % Length(H);
        //循环到底或循环到源点
        count++;
        if(H.elem[address] == NULLKEY || address == HashFun(key,H)) {
            return -1;
        }
    }
    return count;
}
//平均查找长度
int AverageSearchLength(Hash H) {
    int length = H.count;
    int total = 0;
    int num = 0;
    for(int i = 0;i < length;i++) {
        if(H.elem[i] != NULLKEY) {
            num++;
            total += SearchLength(H,H.elem[i]);
        }
    }
    return total / num;
}
//改造搜索，返回下标
Status SearchUpdate(Hash H,int key) {
    int address = HashFun(key,H);
    while(H.elem[address] != key) {
        address = (address+1) % Length(H);
        //循环到底或循环到源点
        if(H.elem[address] == NULLKEY || address == HashFun(key,H)) {
            return -1;
        }
    }
    return address;
}

Status Delete(Hash *H,int key) {
    int index = SearchUpdate(*H,key);
    if(index == -1) {
        return ERROR;
    } else {
        H->elem[index] = NULLKEY;
        return OK;
    }
}

int main() {
    Hash H;
    Init(&H);
    Insert(&H,11);
    Insert(&H,22);
    Insert(&H,33);
    Insert(&H,57);
    Insert(&H,65);
    Insert(&H,31);
    Insert(&H,43);
    Insert(&H,98);
    Insert(&H,77);
    Insert(&H,100);
    Insert(&H,30);
    Insert(&H,28);

    Get(H);
    //Delete(&H,11);
    //Get(H);
 //   Status i = Search(H,35);
   // if(i) {
        printf("Length is %d",SearchLength(H,30));
   //  printf("ASL = %d",AverageSearchLength(H));
  //  } else {
 //       printf("NO");
 //   }
    return 0;
}