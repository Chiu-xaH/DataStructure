#include <stdlib.h>
#include <stdio.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 100
#define NULLKEY 0

typedef int Status;

typedef struct {
    int array[MAXSIZE];
    int length;
} List;

Status Init(List *L,int len,int arr[]) {
    L->length = len;
    for(int i = 0;i < L->length;i++) {
        L->array[i] = arr[i];
    }
    return OK;
}

void Swap(List *L,int i,int j) {
    int temp = L->array[i];
    L->array[i] = L->array[j];
    L->array[j] = temp;
}

void Get(List L) {
    for(int i = 0;i < L.length;i++) {
        printf("%d ",L.array[i]);
    }
    printf("\n");
}
//冒泡排序 O(n^2)
void BubbleSort(List *L) {
    for(int i = 0;i < L->length - 1;i++) {
        for(int j = 0;j < L->length - i - 1;j++) {
            if(L->array[j] > L->array[j+1]) {
                Swap(L,j,j+1);
            }
        }
    }
}
//冒泡排序2
void BubbleSort2(List *L) {
    for(int i = 0;i < L->length;i++) {
        for(int j = L->length - 1;j >= i;j--) {
            if(L->array[j] < L->array[j+1]) {
                Swap(L,j,j+1);
            }
        }
    }
}
//冒泡底部
void BubbleSort3(List *L) {
    for(int i = 0;i < L->length - 1;i++) {
        for(int j = 0;j < L->length - i - 1;j++) {
            if(L->array[j] > L->array[j+1]) {
                Swap(L,j,j+1);
            }
        }
        for(int i = 0;   i < L->length;i++) {
            printf("%d ",L->array[i]);
        } 
        printf("\n");
    }
}
//冒泡排序优化
void BubbleSortUpdate(List *L) {
    Status flag = OK;
    for(int i = 0;i < L->length;i++) {
        flag = ERROR;
        for(int j = L->length - 1;j >= i;j--) {
            if(L->array[j] < L->array[j+1]) {
                Swap(L,j,j+1);
                flag = OK;
            }
        }
    }
}
//直接选择排序 O(n^2)
void SelectSort(List *L) {
    for(int i = 0;i < L->length - 1;i++) {
        int min = i;
        for(int j = i + 1;j < L->length;j++) {
            if(L->array[min] > L->array[j]) {
                min = j;
            }
        }
        if(min != i) {
            Swap(L,min,i);
        }
    }
}
//直接插入排序 O(n^2)
void InsertSort(List *L) {
    for(int i = 1;i < L->length;i++) {
        //当前待插入的元素
        int temp = L->array[i];
        int ptr = i;
        while(ptr > 0 && temp < L->array[ptr-1]) {
            L->array[ptr] = L->array[ptr-1];
            ptr--;
        }
        //插入元素到正确位置
        L->array[ptr] = temp;
    }
}
//希尔排序 O(nlog₂n)
void ShellSort(List *L) {
    for(int gap = L->length / 2;gap > 0;gap /= 2) {
        for(int i = gap;i < L->length;i++) {
            int temp = L->array[i];
            int ptr = i;
            while(ptr >= gap && temp > L->array[ptr-gap]) {
                L->array[ptr] = L->array[ptr-gap];
                ptr -= gap;
            }
            L->array[ptr] = temp;
        }
        printf("GAP = %d | ",gap);
        for(int i = 0;i < L->length;i++) {
            printf("%d ",L->array[i]);
        }
        printf("\n");
    }
}
//快速排序 O(nlog₂n)
void QuickSortRecursive(List *L,int start,int end) {
    if(start >= end) {
        return;
    }
    int mid = L->array[end];
    int left = start,right = end - 1;
    while(left < right) {
        while(left < right && L->array[left] < mid) {
            left++;
        }
        while(left < right && L->array[right] >= mid) {
            right--;
        }
        Swap(L,left,right);
    }
    if(L->array[left] >= L->array[end]) {
        Swap(L,left,end);
    } else {
        left++;
    }
    QuickSortRecursive(L,start,left-1);
    QuickSortRecursive(L,left+1,end);
}

void QuickSort(List *L) {
    QuickSortRecursive(L,0,L->length-1);
}
//堆排序 O(nlog₂n)
//使数组中的下标begin到end建堆
//大根堆
void HeapAdjust(List *L,int begin,int end) {
    int temp = L->array[begin];
    //begin的左孩子，持续向左直到尾
    //找最大的
    for(int i = 2*begin + 1;i <= end;i = 2 * i + 1) {
        //如果右孩子存在，且更大，则右移到那里
        if(i+1 <= end && L->array[i] < L->array[i+1]) {
            i++;
        }
        //如果不如temp大则不需要动
        if(temp >= L->array[i]) {
            break;
        }
        //最大的移动到根节点
        L->array[begin] = L->array[i];
        begin = i;
    }
    //由于上面赋值后，将i原位置也赋给begin，现在将原位置赋值
    L->array[begin] = temp;
}
//小根堆
void HeapAdjust2(List *L,int begin,int end) {
    int temp = L->array[begin];
    for(int i = 2*begin + 1;i <= end;i = 2 * i + 1) {
        //改动
        if(i+1 <= end && L->array[i] > L->array[i+1]) {
            i++;
        }
        //改动
        if(temp <= L->array[i]) {
            break;
        }
        L->array[begin] = L->array[i];
        begin = i;
    }
    L->array[begin] = temp;
}

void HeapSort(List *L) {
    //从数组的中间位置开始，向前遍历来调整堆的结构
    //数组的后半部分都是叶子节点，不需要调整
    for(int i = L->length / 2 - 1;i >= 0;i--) {
        //建堆（大顶堆）
        HeapAdjust2(L,i,L->length - 1);
    }
    for(int i = L->length - 1;i > 0;i--) {
        //根节点于末尾元素交换
        Swap(L,0,i);
        //调整再建堆
        HeapAdjust2(L,0,i-1);
    }
}
//归并排序 O(nlog₂n)
//将SR[start...middle]与TR[middle+1...end]合并为TR[start...end]
void Merge(int SR[],int TR[],int start,int middle,int end) {
    //i, j 分别指向两个子数组的起始位置，k 指向合并后数组的起始位置
    int i = start, j = middle + 1, k = start;

    // 合并两个子数组
    while (i <= middle && j <= end) {
        //归并两个数组并不是简单的拼接，而是进行比较大小
        if (SR[i] <= SR[j]) {
            TR[k++] = SR[i++];
        } else {
            TR[k++] = SR[j++];
        }
    }
    // 如果左半部分有剩余元素，直接复制到 TR
    while (i <= middle) {
        TR[k++] = SR[i++];
    }

    // 如果右半部分有剩余元素，直接复制到 TR
    while (j <= end) {
        TR[k++] = SR[j++];
    }
}

void MergeSortRecursive(int SR[],int TR[],int start,int end){
    int TR2[MAXSIZE];
    if(start == end) {
        TR[start] = SR[start];
    } else {
        int middle = (start+end) / 2;
        MergeSortRecursive(SR,TR2,start,middle);
        MergeSortRecursive(SR,TR2,middle+1,end);
        Merge(TR2,TR,start,middle,end);
    }
}

void MergeSort(List *L) {
    MergeSortRecursive(L->array,L->array,0,L->length-1);
}
//将SR[]中相邻长度为start的子序列两两归并到TR[]
void MergePass(int SR[],int TR[],int start,int end) {
    int i = 0;
    while(i <= end-2*start+1) {
        Merge(SR,TR,i,i+start-1,i+2*start-1);
        i = i+2*start;
    }
    if(i < end-start+1) {
        Merge(SR,TR,i,i+start-1,end);
    } else {
        for(int j = i;j <= end;j++) {
            TR[j] = SR[j];
        }
    }
}

void MergeSortNotRecursive(List *L) {
    int TR[MAXSIZE];
    int k = 1;
    while(k < L->length) {
        MergePass(L->array,TR,k,L->length - 1);
        k *= 2;
        MergePass(TR,L->array,k,L->length - 1);
        k *= 2;
    }
}
//检查是否为堆(type = OK 判断大根堆；type = ERROR 判断小根堆)
Status isHeap(List L,Status type) {
    for(int i = L.length / 2 - 1;i >= 0;i--) {
        int leftChild = 2*i+1;
        int rightChild = 2*i+2;
        if(type) {
            if(leftChild < L.length && L.array[leftChild] > L.array[i]) {
            return ERROR;
            }
            if(rightChild < L.length && L.array[rightChild] > L.array[i]) {
                return ERROR;
            }
        } else {
            if(leftChild < L.length && L.array[leftChild] < L.array[i]) {
                return ERROR;
            }
            if(rightChild < L.length && L.array[rightChild] < L.array[i]) {
                return ERROR;
            }
        } 
    }
    return OK;
}
//建堆递归
void CreateHeap(List *L,int start,int end) {
    int largeest = start;
    int left = 2*start+1;
    int right = 2*start+2;
    if(left < end && L->array[left] < L->array[largeest]) {
        largeest = left;                            
    }
    if(right < end && L->array[right] < L->array[largeest]) {
        largeest = right;
    }
    if(largeest != start) {
        Swap(L,start,largeest);
        CreateHeap(L,largeest,end);
    }
}

void HeapSort3(List *L) {
    for (int i = L->length / 2 - 1; i >= 0; i--) {
        CreateHeap(L, i,L->length - 1);
    }
    for (int i = L->length - 1; i > 0; i--) {
        Swap(L, 0, i);  
        // 缩小堆的范围
        CreateHeap(L,0,i-1); 
    }
}

void HeapAdjustUpdate(List *L,int start,int end) {
    int ptr = start,left = start*2+1,right = start*2+2;
    if(left < end && L->array[left] > L->array[ptr]) {
        ptr = left;
    }
    if(right < end && L->array[right] > L->array[ptr]) {
        ptr = right;
    }
    if(ptr != start) {
        Swap(L,start,ptr);
        HeapAdjustUpdate(L,ptr,end);
    }
}

void HeapSortUpdate(List *L) {
    for(int i = L->length / 2 - 1;i >= 0;i--) {
        HeapAdjustUpdate(L,i,L->length);
    }
    for(int i = L->length - 1;i > 0;i--) {
        Swap(L,0,i);
        HeapAdjustUpdate(L,0,i);
    }
}

//设计算法实现功能：不用完整排序，求解出按大小关系为第k位的元素
int GetElem(List *L,int place) {
    for (int i = L->length / 2 - 1; i >= 0; i--) {
        CreateHeap(L, i,L->length - 1);
    }
    for (int i = L->length - 1; i > place-1; i--) {
        Swap(L, 0, i);  
        // 缩小堆的范围
        CreateHeap(L,0,i-1); 
    }
    return L->array[0];
}
//设计算法将其调整为三部分，其中左边所有元素为3的倍数，中间所有元素除3余1，右边所有元素除3余2，时间复杂度为O(n)
void Question(List *L) {
    int left = 0;
    int right = L->length-1;
    while(left < right) {
        if(L->array[left] % 3 == 0) {
            left++;
        }
        if(L->array[right] % 3 == 1 || L->array[right] % 3 == 2) {
            right--;
        }
        if(L->array[left] % 3 != 0 && left < right) {
            Swap(L,left,right);
        } else if(L->array[left] % 3 == 0 && left < right) {
            Swap(L,left,right);
        }
    }
    left = right+1;
    right = L->length-1;
    while(left < right) {
        if(L->array[left] % 3 == 1) {
            left++;
        }
        if(L->array[right] % 3 == 2) {
            right--;
        }
        if(L->array[left] % 3 != 1 && left < right) {
            Swap(L,left,right);
        } else if(L->array[left] % 3 != 2 && left < right) {
            Swap(L,left,right);
        }
    }
}

void QuestionUpdate(List *L) {
    int left = 0;
    int current = 0;
    int right = L->length - 1;
    
    while (current <= right) {
        if (L->array[current] % 3 == 0) {
            Swap(L, left, current);
            left++;
            current++;
        } else if (L->array[current] % 3 == 1) {
            current++;
        } else {
            Swap(L, current, right);
            right--;
        }
    }
}
//如果递增有序的数据表A、B分别代表一个集合，设计算法以求解此类集合的交、并差等运算
/*交集
使用两个指针分别指向 A 和 B 的第一个元素。
比较 A 和 B 当前指向的元素。
如果相等，说明该元素在交集中，记录该元素，然后两个指针都移动到下一个元素。
如果 A 的元素小于 B 的元素，移动 A 的指针。
反之，移动 B 的指针。
重复直到其中一个指针超出数组范围。
*/
/*并集
比较 A 和 B 当前指向的元素。
如果相等，将该元素加入并集，然后两个指针都移动到下一个元素。
如果 A 的元素小于 B 的元素，将 A 的元素加入并集，并移动 A 的指针。
如果 B 的元素小于 A 的元素，将 B 的元素加入并集，并移动 B 的指针。
重复直到其中一个指针超出数组范围，最后将剩余的元素直接加入并集中。
*/
/*差集
使用两个指针分别指向 A 和 B 的第一个元素。
如果 A 的元素小于 B 的元素，将 A 的元素加入差集，并移动 A 的指针。
如果 A 的元素等于 B 的元素，跳过该元素并同时移动 A 和 B 的指针。
如果 A 的元素大于 B 的元素，只移动 B 的指针。
重复直到 A 的指针超出数组范围。
*/
void Set() {
    int sizeA = 5,sizeB = 4;
    int A[] = { 1,2,3,4,5 };
    int B[] = { 2,4,6,8 };
    int C[sizeA+sizeB];
    //交集
    int ptrA = 0,ptrB = 0,i = 0,ptr = 0;
    while(ptrA < sizeA && ptrB < sizeB) {
        if(A[ptrA] < B[ptrB] && ptrA < sizeA) {
            ptrA++;
        } else if(A[ptrA] > B[ptrB] && ptrB < sizeB) {
            ptrB++;
        } else if(A[ptrA] == B[ptrB]) {
            C[i] = A[ptrA];
            ptrA++;
            ptrB++;
            i++;
        }
    }
    //并集
    ptrA = 0,ptrB = 0,i = 0,ptr = 0;
    //当其中一个越界就结束循环
    while(ptrA < sizeA && ptrB < sizeB) {
        if(A[ptrA] < B[ptrB] && ptrA < sizeA) {
            C[i] = A[ptrA];
            i++;
            ptrA++;
        } else if(A[ptrA] > B[ptrB] && ptrB < sizeB) {
            C[i] = B[ptrB];
            i++;
            ptrB++;
        } else if(A[ptrA] == B[ptrB]) {
            C[i] = A[ptrA];
            ptrA++;
            ptrB++;
            i++;
        }
    }
    ///处理剩下的
    while(ptrA < sizeA) {
        C[i] = A[ptrA];
        ptrA++;
        i++;
    }
    while(ptrB < sizeB) {
        C[i] = B[ptrB];
        ptrB++;
        i++;
    }
    //差集
    ptrA = 0,ptrB = 0,i = 0,ptr = 0;
    while(ptrA < sizeA && ptrB < sizeB) {
        if(A[ptrA] < B[ptrB] && ptrA < sizeA) {
            C[i] = A[ptrA];
            i++;
            ptrA++;
        } else if(A[ptrA] > B[ptrB] && ptrB < sizeB) {
            ptrB++;
        } else if(A[ptrA] == B[ptrB]) {
            ptrA++;
            ptrB++;
        }
    }
    //打印
    for(int j = 0;j < i;j++) {
        printf("%d ",C[j]);
    }
}
// 4)	Top-k问题，设计算法实现在不完全排序情况下，在n个数据中选出k个最小（最大）数据，要求数据比较次数尽可能少。（不得使用STL的priority-queue，自建k个结点的堆完成）。
// 按链式基数排序的方法实现对整数表的排序。（非必做内容）

int main() {
    int arr[] = { 
       // 22,34,3,32,82,55,89,50,37,5,64,35,9,70
       //230,100,120,90,86,55,78,33,80,15,64,12,46,30,45
      // 120 ,90 ,105 ,30 ,85 ,50 ,100 ,28 ,25 ,15 ,60 ,30 ,40 ,78 ,10, 12
       //10 ,12 ,35 ,25 ,15 ,40 ,78 ,28 ,90 ,85 ,60 ,50 ,105 ,120 ,100 ,30
       //10,12,27,13,36,96,24,36,70,100,49,79
       //10,24,36,70,27,13,49,36,79,100,96
       //125,100,22,34,20,44,76,66,11,8,14,15,2,5,1
     //  100,80,55,60,50,40,35,58,20
     //3,5,22,34,11,44,76,61,100,25,14,120
     9,4,7,4,2,6
         };
    Status I;
    List L;
    I = Init(&L,6,arr);
    BubbleSort3(&L);
    //Get(L);
    //BubbleSort(&L);
    //SelectSort(&L);
    //InsertSort(&L);
   // ShellSort(&L);
    //QuickSort(&L);
    //MergeSort(&L);
    //120 105 100 90 85 78 60 50 40 35 30 28 25 15 12 10
    //int ele = 14;
    //printf("The %d Elem is %d",ele,GetElem(&L,ele));
    //Get(L);
    //I = isHeap(L,ERROR);
    //if(I) {
      //  printf("YES");
    //} else printf("NO");
   // HeapSortUpdate(&L);
    //QuestionUpdate(&L);
    //Get(L);
    //Set();
}