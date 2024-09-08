#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
#define OK 1
#define ERROR 0

typedef char ElemType;
typedef int Status;

typedef struct {
    ElemType data[MAXSIZE];
    int last;
} List;

Status Init(List *L) {
    L->last = -1;
    return OK;
}
                    
Status Insert(List *L,ElemType E,int place) {
    L->last++;
    if(L->last >= MAXSIZE)
        return ERROR;

    int ptr = L->last+1;
    while(ptr != place) {
        L->data[ptr - 1] = L->data[ptr - 2];
        ptr--;
    }
    L->data[ptr - 1] = E;
    return OK;
}

Status Add(List *L,ElemType E) {
    L->last++;
    if(L->last >= MAXSIZE)
        return ERROR;
    L->data[L->last] = E;
    return OK;
}

int Length(List *L) {
    return L->last + 1;
}

Status DelelteTail(List *L) {
    if(L->last == -1) {
        return ERROR;
    }
    L->last--;
    return OK;
}

Status Delete(List *L,int palce) {
    //前移，与插入相反
    //COUNT  1   2   3   4   5   6
    //INDEX  0   1   2   3   4   5
    //      [A]-[B]-[C]-[D]-[E]-[F]
    if(L->last == -1) {
        return ERROR;
    }
    int ptr = L->last+1;
    while(ptr != palce) {
        L->data[ptr-2] = L->data[ptr-1];
        ptr--;
    }
    L->last--;
    return OK;
}

Status Get(List L) {
    if(L.last == -1)
        return ERROR;
    if(L.last >= MAXSIZE)
        return ERROR;
    int i = 0;
    while(i != L.last+1) {
        printf("%c ",L.data[i]);
        i++;
    }
    printf("\n");
    return OK;
}

int main() {
    Status i;
    List L;
    i = Init(&L);
    i = Add(&L,'A');
    i = Add(&L,'B');
    i = Add(&L,'D');
    i = Insert(&L,'C',3);
    Delete(&L,3);
    ///i = DelelteTail(&L);
    i = Get(L);
    return 0;
}
