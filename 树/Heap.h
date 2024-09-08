void Swap(int array[],int i,int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void CreateHeap(int array[],int start,int end) {
    int largeest = start;
    int left = 2*start+1;
    int right = 2*start+2;
    if(left < end && array[left] < array[largeest]) {
        largeest = left;
    }
    if(right < end && array[right] < array[largeest]) {
        largeest = right;
    }
    if(largeest != start) {
        Swap(array,start,largeest);
        CreateHeap(array,largeest,end);
    }
}

//取出根节点（最小值）
int GetRoot(int array[]) {
    HeapSort(array,2,8);
    int total = array[0] + array[1];
}
//插入
void Insert(int array[],int data) {
    
}

int HeapSort(int array[],int length) {
    for (int i = length / 2 - 1; i >= 0; i--) {
        CreateHeap(array, i,length - 1);
    }
    for (int i = length - 1; i > 0; i--) {
        Swap(array, 0, i);  
        // 缩小堆的范围
        CreateHeap(array,0,i-1); 
    }
}

int GetElem(int array[],int place,int length) {
    for (int i = length / 2 - 1; i >= 0; i--) {
        CreateHeap(array, i,length - 1);
    }
    for (int i = length - 1; i > place-1; i--) {
        Swap(array, 0, i);  
        // 缩小堆的范围
        CreateHeap(array,0,i-1); 
    }
    return array[0];
}