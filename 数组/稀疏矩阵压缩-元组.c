#include <stdio.h>

#define EMPTY 0
#define OK 1
#define ERROR 0
#define SIZE 4

typedef int Status;
typedef int ElemType;

typedef struct {
    int i,j;
    ElemType ele;
} Tuple;

typedef struct {
    int mu,nu,tu;
    //行数//列数//非0元个数
    Tuple data[SIZE * SIZE];
} TupleList;

Status Init(TupleList *T) {
    T->mu = SIZE;
    T->nu = SIZE;
    T->tu = 0;
    return OK;
}

Status Get(TupleList *T) {
    int count = T->tu;
    printf("Not 0 count is %d\n",count);
    for(int i = count - 1;i >= 0;i--) {
        Tuple tuple = T->data[i];
        printf("%d is in A[%d][%d]\n",tuple.ele,tuple.i,tuple.j);
    }
    return OK;
}
//矩阵2加到矩阵1上
Status Plus(TupleList *T1, TupleList *T2) {
    int count1 = T1->tu, count2 = T2->tu;
    for(int i = 0; i < count2; i++) {
        Tuple tuple2 = T2->data[i];
        int found = 0;
        for(int j = 0; j < count1; j++) {
            Tuple *tuple1 = &T1->data[j];
            //将2的数据累加到相同的1上
            if(tuple1->i == tuple2.i && tuple1->j == tuple2.j) {
                tuple1->ele += tuple2.ele;
                found = 1;
                break;
            }
        }
        //开辟新的表
        if(!found) {
            T1->data[T1->tu] = tuple2;
            T1->tu++;
        }
    }
    return OK;
}

Status Transfer(TupleList *T) {
    int A[T->mu][T->nu];
    //初始化
    for(int i = 0;i < T->mu;i++) {
        for(int j = 0;j < T->nu;j++) {
            A[i][j] = 0;
        }
    }
    for(int i = 0;i < T->tu;i++) {
        Tuple tuple = T->data[i];
        A[tuple.i][tuple.j] = tuple.ele;
    }
    for(int i = 0;i < T->mu;i++) {
        for(int j = 0;j < T->nu;j++) {
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    return OK;
}

int main() {
    int A[SIZE][SIZE] = {
        {0,0,0,1},
        {0,3,0,0},
        {0,0,0,0},
        {0,8,0,5}
    };
    int B[SIZE][SIZE] = {
        {0,0,0,0},
        {0,8,0,0},
        {0,0,0,5},
        {1,8,0,5}
    };
    /*
    0 0 0 1
    0 11 0 0
    0 0 0 5
    1 16 0 10 
    */
    TupleList List,List2;
    Init(&List);
    Init(&List2);
    for(int i = 0;i < SIZE;i++) {
        for(int j = 0;j < SIZE;j++) {
            int elem = A[i][j];
            if(elem != 0) {
                //保存进去i,j,elem
                Tuple tuple;
                tuple.ele = elem;
                tuple.i = i;
                tuple.j = j;
                List.data[List.tu] = tuple;
                List.tu++;
            }
        }
    }
   // Get(&List);
   Transfer(&List);
    for(int i = 0;i < SIZE;i++) {
        for(int j = 0;j < SIZE;j++) {
            int elem = B[i][j];
            if(elem != 0) {
                //保存进去i,j,elem
                Tuple tuple;
                tuple.ele = elem;
                tuple.i = i;
                tuple.j = j;
                List2.data[List2.tu] = tuple;
                List2.tu++;
            }
        }
    }
   // Get(&List2);
    Plus(&List,&List2);
   // Get(&List);
   // Transfer(&List);
}