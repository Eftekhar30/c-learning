#include <stdio.h>

int main(){

    int arr[10] = {1,2,3,4,5};
    int pos = 1, i = pos, n = 5;
    while(i<n){
        arr[i] = arr[i+1];
        i++;
    }
    n--;
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}