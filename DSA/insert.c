#include <stdio.h>

int main(){

    int arr[10] = {1,2,3,4,5};
    int item = 10, pos = 3, n=5;
    int i = n-1;
    n= n+1;
    while(i>=pos){
        arr[i+1] = arr[i];
        i--;
    }
    arr[pos] = item;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}