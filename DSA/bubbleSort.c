#include <stdio.h>

int main(){

    int arr[10] = {5,4,3,2,1};
    int pass = 1, n = 5;
    while (pass < n) {
        for (int i = 0; i < n - pass; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        pass++;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }


    return 0;
}