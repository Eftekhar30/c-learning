#include <stdio.h>

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