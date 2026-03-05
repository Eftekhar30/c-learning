#include<iostream>
using namespace std;
void sort(int array[], int size){
    int temp;
    for(int i = 0; i < size-1; i++){
        for(int j = 0; j < size - i -1; j++){
            if(array[j]> array[j+1]){
                temp = array[j];
                array[j]= array[j+1];
                array[j+1] = temp;
            }
        }
    }
}
int main(){
    int arr[10]= {10, 2, 3,6,4,5,7,8,9,1};
    int size = sizeof(arr)/sizeof(arr[0]);

    sort(arr, size);

    for(int element : arr){
        cout << element <<" ";
    }

    return 0;
}