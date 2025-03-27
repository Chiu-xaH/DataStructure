#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define EQUAL 0
#define BIGGER 1
#define SMALLER -1

typedef int ElemType;
typedef int Status;
typedef struct {
    ElemType data[MAXSIZE];
    int count;
} List;

Status Init(List *L) {
    L->count = 0;
    return OK;
}                      
//COUNT  1   2   3   4   5   6
//INDEX  0   1   2   3   4   5
//      [A]-[B]-[C]-[]-[E]-[F]
//place == 4  count == 6
Status Insert(List *L,ElemType E,int place) {
    L->count++;
    if(L->count > MAXSIZE)
        return ERROR;

    int ptr = L->count;
    while(ptr != place) {
        L->data[ptr - 1] = L->data[ptr - 2];
        ptr--;
    }
    L->data[ptr - 1] = E;
    return OK;
}

Status Add(List *L,ElemType E) {
    if(L->count == MAXSIZE) {
        return ERROR;
    }
    L->data[L->count] = E;
    L->count++;
    return OK;
}

int Length(List *L) {
    return L->count;
}

Status DelelteTail(List *L) {
    if(L->count == 0) {
        return ERROR;
    }
    L->count--;
    return OK;
}

Status Delete(List *L,int palce) {
    //前移，与插入相反
    //COUNT  1   2   3   4   5   6
    //INDEX  0   1   2   3   4   5
    //      [A]-[B]-[D]-[E]-[F]-[F]
    if(L->count == 0) {
        return ERROR;
    }
    int ptr = palce-1;
    while(ptr+1 != L->count) {
        L->data[ptr] = L->data[ptr+1];
        ptr++;
    }
    L->count--;
    return OK;
}

Status Get(List L) {
    if(L.count == 0)
        return ERROR;
    if(L.count > MAXSIZE)
        return ERROR;
    int i = 0;
    while(i != L.count) {
        printf("%d ",L.data[i]);
        i++;
    }
    printf("\n");
    return OK;
}
//（不考虑负数）用顺序表表示较多位数的大整数，分别写出这类大数的比较、加减乘除等运算，并分析算法的时间性能
//得到位数
int counts(int num) {
    int count = 0;
    if(num == 0) {
        return 1;
    }
    while(num != 0) {
        num /= 10;
        count++;
    }
    return count;
}
//得到指定位数
int getNum(int num,int count) {
    int weiShu = counts(num);
    int divisor = (int)pow(10, weiShu - count);
    int digit = (num / divisor) % 10;
}
//将数字转换为列表
List Transfer(int num) {
    //假设num是12345
    int weiShu = counts(num);
    List L;
    Init(&L);
    L.count = MAXSIZE;
    for(int i = 0;i < MAXSIZE;i++) {
        L.data[i] = 0;
    }
    int place = weiShu;
    int ptr = L.count-1;
    while(place != 0) {
        L.data[ptr] = getNum(num,place);
        ptr--;
        place--;
    }
    return L;
}
//比较
Status Compare(int num1,int num2) {
    List list1 = Transfer(num1);
    List list2 = Transfer(num2);
    int ptr1 = 0,ptr2 = 0;
    while(ptr1 != list1.count && ptr2 != list2.count) {
        if(list1.data[ptr1] > list2.data[ptr2]) {
            return BIGGER;
        } else if (list1.data[ptr1] < list2.data[ptr2]) {
            return SMALLER;
        } else {
            ptr1++;
            ptr2++;
        }
    }
    return EQUAL;
}
//输出数字
void Print(List L) {
    int i = 0,ptr = 0;
    while(L.data[i] == 0) {
        i++;
    }
    while(i != L.count) {
        printf("%d",L.data[i]);
        i++;
    }
    printf("\n");
}
//加//进位
List Plus(int num1,int num2) {
    List list1 = Transfer(num1);
    List list2 = Transfer(num2);
    
    int ptr = 0;
    while(ptr != list2.count) {
        list1.data[ptr] += list2.data[ptr]; 
        ptr++;
    }
    
    //进位
    ptr = MAXSIZE-1;
    while(ptr != 0) {
        if(list1.data[ptr] >= 10) {
            list1.data[ptr] -= 10;
            list1.data[ptr-1] += 1;
        }
        ptr--;
    }
    return list1;
}
//减//借位
List Subtract(int num1,int num2) {
    List list1 = Transfer(num1);
    List list2 = Transfer(num2);
    
    int ptr = 0;
    while(ptr != list2.count) {
        list1.data[ptr] -= list2.data[ptr]; 
        ptr++;
    }
    
    //借位
    ptr = MAXSIZE-1;
    while(ptr != 0) {
        if(list1.data[ptr] < 0) {
            list1.data[ptr] += 10;
            list1.data[ptr-1] -= 1;
        }
        ptr--;
    }
    return list1;
}
//乘//交错相加
List Multi(int num1,int num2) {
    int weiShu1 = counts(num1);
    int weiShu2 = counts(num2);
    List list1 = Transfer(num1);
    List list2 = Transfer(num2);
    //初始化list3
    List list3;
    Init(&list3);
    for(int i = 0;i < MAXSIZE;i++)
    list3.data[i] = 0;

    list3.count = MAXSIZE;
    //开始计算
    int ptr2 = MAXSIZE-1,ptr1 = MAXSIZE-1,ptr3 = MAXSIZE-1,count = 0;
    while(ptr2 >= 0) {
        ptr1 = MAXSIZE-1;
        ptr3 = ptr1 - count;
        while(ptr1 >= 0) {
            list3.data[ptr3] += (list1.data[ptr1] * list2.data[ptr2]);
            ptr1--;
            ptr3--;
        }
        count++;
        ptr2--;
    }

    //进位
    ptr3 = MAXSIZE-1;
    while(ptr3 != 0) {
        if(list3.data[ptr3] >= 10) {
            int i = list3.data[ptr3] / 10;
            list3.data[ptr3] -= i*10;
            list3.data[ptr3-1] += i;
        }
        ptr3--;
    }
    return list3;
}
//除//
List Divide(int num1,int num2) {
    //没什么思路
}
//列表递增 设计算法实现集合并、交、差、子集
//list1={1,2,3,4,5}
//list2={2,4,6}
List JointSet(List list1,List list2) {
    int ptr1 = 0,ptr2 = 0;
    List new;
    Init(&new);
    while (ptr1 != list1.count && ptr2 != list2.count) {
        int data1 = list1.data[ptr1];
        int data2 = list2.data[ptr2];
        if(data1 > data2) {
            ptr2++;
        } else if(data1 < data2) {
            ptr1++;
        } else {
            new.data[new.count] = data1;
            new.count++;
            ptr1++;
            ptr2++;
        }
    }
    return new;
}
//list1={1,2,3,4,5}
//list2={2,4,6}
void LinkSet(List *list1,List list2) {
    int ptr1 = 0,ptr2 = 0;
    while (ptr1 != list1->count && ptr2 != list2.count) {
        int data1 = list1->data[ptr1];
        int data2 = list2.data[ptr2];
        if(data1 > data2) {
            Add(list1,data2);
            ptr2++;
        } else if(data1 < data2) {
            ptr1++;
        } else {
            ptr1++;
            ptr2++;
        }
    }
    while(ptr2 != list2.count) {
        Add(list1,list2.data[ptr2]);
        ptr2++;
    }
}
//list1={1,2,3,4,5}
//list2={2,4,6}
Status SubSet(List list1,List list2) {
    int ptr1 = 0,ptr2 = 0, count = 0;
    while (ptr1 != list1.count && ptr2 != list2.count) {
        int data1 = list1.data[ptr1];
        int data2 = list2.data[ptr2];
        if(data1 > data2) {
            ptr2++;
        } else if(data1 < data2) {
            ptr1++;
        } else {
            ptr1++;
            ptr2++;
            count++;
        }
    }
    if(ptr2 != list2.count) {
        return ERROR;
    } else {
        if(count != list2.count) {
            return ERROR;
        }
    }
    return OK;
}
//list1={1,2,3,4,5}
//list2={2,4}
void DifferentSet(List *list1,List list2) {
    int ptr1 = 0,ptr2 = 0,count = 0;
    int array[list1->count];
    while (ptr1 != list1->count && ptr2 != list2.count) {
        int data1 = list1->data[ptr1];
        int data2 = list2.data[ptr2];
        if(data1 > data2) {
            ptr2++;
        } else if(data1 < data2) {
            ptr1++;
        } else {
            Delete(list1,ptr1+1);
            ptr2++;
        }
    }   
}
//列表递增 设计算法插入元素，仍保持有序，且插入后无重复元素，有则不插入,要求时间尽可能少
//{1,2,3,4,6,7,8,9}
void InsertUpdate(List *L,ElemType E) {
    int ptr = 0;
    while(ptr != L->count) {
        if(L->data[ptr] < E) {
            ptr++;
        } else if(L->data[ptr] > E) {
            break;
        } else {
            return;
        }
    }
    Insert(L,E,ptr+1);
}
//设计算法去重顺序表中元素
void Swap(List *L,int i,int j) {
    int temp = L->data[i];
    L->data[i] = L->data[j];
    L->data[j] = temp; 
}

void SelectSort(List *L) {
    for(int i = 0;i < L->count - 1;i++) {
        int min = i;
        for(int j = i+1;j < L->count;j++) {
            if(L->data[min] > L->data[j]) {
                min = j;
            }
        }
        if(min != i) {
            Swap(L,min,i);
        }
    }
}
//列表递增 设计算法去重，要求时间尽可能少
//(1,1,2,2,2,3,4,5,5,5,6,6,7,7,8,8,8,9)模拟执行，统计次数，分析时间性能
//补充说明：下面的算法尽管可以实现需求，但是可以优化，设置两个指针，same变量，记录相同数字的个数，在删除移位的时候按same个移动，而不是一个一个挪，具体实现交给大家补充(DeWightRe)了
void DeWeightUpdate(List *L) {
    int left = 0,right = left+1,count = 0;
    while(left != L->count) {
        if(L->data[left] == L->data[right]) {
            //去重
            count++;
            Delete(L,right+1);
        } else {
            //右移
            left++;
            if(left+1 < L->count)
            right = left+1;
        }
    }
    L->count++;
    // printf("Runned %d times\n",count);
}
// 优化版 
void DeWeightUpdate2(List *L) {
    int left = 0,right = 1,same = 0,count = 0;
    while (right != L->count) {
        if (L->data[left] == L->data[right]) {
            same++;
        } else {
            if (same > 0) {
                // 批量右移，减少移动次数
                for (int i = right; i < L->count; i++) {
                    L->data[i - same] = L->data[i];
                }
                count++;
                L->count -= same; // 更新元素个数
                right -= same; // 调整 right
                same = 0;
            }
            left = right;
        }
        right++;
    }
    // 处理末尾情况
    if (same > 0) {
        L->count -= same;
    }
    printf("Runned %d times\n",count);
}


void DeWeight(List *L) {
    SelectSort(L);
    DeWeightUpdate(L);
}

void DeWeightRe() {}

int main() {
    Status i;
    List L1,L2;
    i = Init(&L1);
    i = Init(&L2);
  //  i = Add(&L,'A');
  //  i = Add(&L,'B');
  //  i = Add(&L,'D');
   // i = Insert(&L,'C',3);
   // Delete(&L,3);
    ///i = DelelteTail(&L);
    //i = Get(L);
   // i = getNum(12345,3);
    //printf("%d",i);
 //   i = Compare(1345,12345);
   // if(i == EQUAL) {
    //    printf("EQUAL");
   // } else if(i == BIGGER) {
     //   printf("NUM1 > NUM2");
  //  } else if(i == SMALLER) {
    //    printf("NUM1 < NUM2");
   // }
   //List L = Multi(345772,28);
   //345772
   //000028
   //01
   //
   //345772
   //Print(L);
   ///(1,1,2,2,2,3,4,5,5,5,6,6,7,7,8,8,8,9)
    Add(&L1,1);
    Add(&L1,1);
    Add(&L1,2);
    Add(&L1,2);
    Add(&L1,2);
    Add(&L1,3);
    Add(&L1,4);
    Add(&L1,5);
    Add(&L1,5);
    Add(&L1,5);
    Add(&L1,6);
    Add(&L1,6);
    Add(&L1,7);
    Add(&L1,7);
    Add(&L1,8);
    Add(&L1,8);
    Add(&L1,8);
    Add(&L1,9);
    //Add(&L2,0);
   // Add(&L2,2);
    //Add(&L2,4);
    //Add(&L2,6);
   // List list = JointSet(L1,L2);
   // LinkSet(&L1,L2);
    //Get(L1);
    //i = SubSet(L1,L2);
    //if(i) {
      //  printf("YES");
    //} else {
      //  printf("NO");
   // }
    //DifferentSet(&L1,L2);
    Get(L1);
    DeWeightUpdate2(&L1);
    // Delete(&L1,5);
    // Get(L1);
    // InsertUpdate(&L1,5);
    Get(L1);
    return 0;
}