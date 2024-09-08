#include <stdio.h>

#define FAILURE -1
#define OK 1
#define ERROR 0
#define SIZE 10

typedef int Status;

//顺序查找O(n)
int SequentialSearch(int arr[],int length,int key) {
    for(int i = 0;i < length;i++) {
        if(arr[i] == key) {
            return i;
        }
    }
    return FAILURE;
}
//改进顺序查找-设置哨兵
int SequentialSearchUpdate(int arr[],int length,int key) {
    //[0]位置作为哨兵，数据从[1]开始存储
    arr[0] = key;
    int i = length;
    while(arr[i] != key) {
        i--;
    }
    return i;
}
//二分查找（折半查找）O(logn)(要求数组分布均匀)
int BinarySearch(int arr[],int length,int key) {
    int low = 0,high = length-1;
    int mid;
    while(low <= high) {
        mid  = (low+high) / 2;
        if(key < arr[mid]) {
            high = mid -1;
        } else if(key > arr[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return FAILURE;
}
//二分递归
int BinarySearchRecursive(int arr[],int low,int high,int key) {
    if(low > high) {
        return FAILURE;
    } else {
        int mid = (low+high) / 2;
        if(arr[mid] > key) {
            return BinarySearchRecursive(arr,low,mid-1,key);
        } else if(arr[mid] < key) {
            return BinarySearchRecursive(arr,mid+1,high,key);
        } else {
            return mid;
        }
    }
}
//二分改进-插值查找 O(log₂n)
//𝑚𝑖𝑑 = 𝑙𝑜𝑤 + (𝑘𝑒𝑦 −𝐴[𝑙𝑜𝑤])/(𝐴[ℎ𝑖𝑔ℎ]−𝐴[𝑙𝑜𝑤])*(ℎ𝑖𝑔ℎ − 𝑙𝑜𝑤)
int InterpolationSearch(int arr[],int length,int key) {
    int low = 0,high = length-1;
    int mid;
    while(low <= high) {
        mid  = low + (high-low)*(key-arr[low])/(arr[high]-arr[low]);
        if(key < arr[mid]) {
            high = mid -1;
        } else if(key > arr[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return FAILURE;
}
//斐波那契查找 O(log₂n)
int F[SIZE];
//斐波那契数列：0，1，往后每一项等于前两项之和
Status InitFibonacci(int F[],int length) {
    if(length == 0) return ERROR;
    else if(length == 1) {
        F[0] = 0;
    } else  {
        F[0] = 0;
        F[1] = 1;
        for(int i = 2;i < length;i++) {
            F[i] = F[i-1] + F[i-2];
        } 
    }
    return OK;
}

int FibonacciSearch(int arr[],int length,int key) {
    int low = 1,high = length,mid;
    int k = 0;
    //选出斐波那契数列F[]中比length大但是最靠近长度的那个值的下标
    while(length > F[k]-1) {
        k++;
    }
    //length=10，F[6]=8,F[7]=13,所以k=7 
    //将不满的数值补全为末尾值
    for(int i = length;i < F[k]-1;i++) {
        arr[i] = arr[length];
    }
    while(low <= high) {
        mid = low + F[k-1]-1;
        if(key < arr[mid]) {
            high = mid - 1;
            k -= 2;
        } else if(key > arr[mid]) {
            low = mid + 1;
            k -= 2;
        } else {
            if(mid <= length) {
                return mid;
            } else {
                return length;
            }
        }
    }
    return FAILURE;
}
//设计算法构造n个元素（下标1~n）的二分查找判定树
typedef struct Node {
    int key;
    struct Node *leftChild,*rightChild;
}Node,*Tree;

Tree newNode(int key) {
    Tree new = (Tree)malloc(sizeof(Node));
    new->key = key;
    new->leftChild = new->rightChild = NULL;
    return new;
}

Tree CreateTree(int arr[],int start,int end) {
    if(start > end) {
        return NULL;
    }

    int middle = (start+end)/2;
    Tree root = newNode(arr[middle]);

    root->leftChild = CreateTree(arr,start,middle-1);
    root->rightChild = CreateTree(arr,middle+1,end);
    return root;
}

int main() {
    int arr[SIZE+1] = { 0,1,2,3,4,5,6,7,8 };
    int key;
    printf("Input you want to serch\n");
    scanf("%d",&key);

    int index = InterpolationSearch(arr,SIZE,key)
    //SequentialSearch(arr,SIZE,key)
    ;
    if(index != FAILURE) {
        printf("Searched %d in array[%d]",key,index);
    } else {
        printf("No");
    }
  InitFibonacci(F,SIZE);
  //for(int i = 0;i < SIZE;i++)
   // printf("%d ",F[i]);
}