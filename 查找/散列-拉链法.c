#include "LinkList.h"

#define SIZE 120
#define NULLKEY -32768

typedef struct {
    Node *elem;//动态分配数组
    int count;
} Hash;

Status Init(Hash *H) {
    H->count = SIZE;
    H->elem = (LinkList)malloc(H->count * sizeof(Node));
    for(int i = 0;i < H->count;i++) {
        H->elem[i].data = NULLKEY;
        H->elem[i].next = NULL;
    }
    return OK;
}

int Length(Hash H) {
    return H.count;
}

int HashFun(int key) {
    return key % 4;
}


void Insert(Hash *H,int key) {
    //拉链法解决冲突，寻找空位
    int address = HashFun(key);
    if(H->elem[address].data != NULLKEY) {
        LinkList list = &H->elem[address];
        LinkList new = (LinkList)malloc(sizeof(Node));
        new->data = key;
        new->next = NULL;
        while(list->next != NULL) {
            list = list->next;
        }
        list->next = new;
    } else {
        H->elem[address].data = key;
    }
}

void Get(Hash H) {
    for(int i = 0;i < Length(H);i++) {
        LinkList list = &H.elem[i];
        if(list->data != NULLKEY) {
            while(list != NULL) {
                printf("%d ",list->data);
                list = list->next;
            }
        }
    }
    printf("\n");
}

Status Search(Hash H,int key) {
    int address = HashFun(key);
    LinkList list = &H.elem[address];
    while(list) {
        if(list->data == key) {
            return OK;
        }
        list = list->next;
    }
    return ERROR;
}

int TransferLetter(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        return letter - 'A' + 1;
    } else {
        return -1;
    }
}

int SearchLength(Hash H,int key) {
    int length = 1;
    int address = HashFun(key);
    LinkList list = &H.elem[address];
    while(list) {
        if(list->data == key) {
            return length;
        }
        length++;
        list = list->next;
    }
    return -1;
}

double AverageSearchLength(Hash H) {
    double total = 0;
    int num = 0;
    for(int i = 0;i < Length(H);i++) {
        LinkList list = &H.elem[i];
        if(list->data != NULLKEY) {
            while(list != NULL) {
                num++;
                total += SearchLength(H,H.elem[i].data);
                list = list->next;
            }
        }
    }
    return total / num;
}


int main() {
    Hash H;
    Init(&H);
    Insert(&H,11);
    Insert(&H,22);
    Insert(&H,35);
    Insert(&H,48);
    Insert(&H,53);
    Insert(&H,62);
    Insert(&H,71);
    Insert(&H,85);

    Get(H);
   // int key = 62;
   // Status I = Search(H,key);
    //if(I) {
   //     printf("YES LENGTH IS %d",SearchLength(H,key));
  //  } else {
   //     printf("NO");
  //  }
  printf("ASL = %d\n",AverageSearchLength(H));
  char letter = 'F';
  printf("%d",TransferLetter(letter));
}