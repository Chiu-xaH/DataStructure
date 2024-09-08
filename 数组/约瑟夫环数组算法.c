#include<stdio.h>
int main()
{
    int arr[400] = {0};
    int i = 0;
    int n = 41;
    for(i = 0; i < n; i++){
        arr[i] = i + 1;
    }
    for(i = 0; i < n; i++){
        if((i + 1) % 3 != 0){
            arr[n++] = arr[i];
        }
    }
    printf("%d\t", arr[n-1]);
    return 0;
}