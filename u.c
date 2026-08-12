#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50}; 
    int pos = 2; 
    int n = 5;   
    
    int j = pos; 
    
    while (j < n - 1) {
        arr[j] = arr[j + 1];
        j = j + 1;
    }
    
    n--; 
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}#include <stdio.h>

int main(){

    int arr[5] = {1,2,3,4,5};
    int target= 3;
    for(int i = 0; i<5;i++){
        if(target == arr[i]){
            printf("%d has been found & Position: %d", arr[i], i);
            break;
        }
    }

    return 0;
}