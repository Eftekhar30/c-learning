#include<stdio.h>
int main(){
    int z;
    int sum=0;

    scanf("%d", &z);
    
    int a[z];
    
    for(int i=0; i<z; i++){
        scanf("%d", &a[i]);
        
        sum += a[i];
    }
    printf("%d", sum);

    return 0;
}