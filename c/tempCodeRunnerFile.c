#include<stdio.h>

int main(){
    int start, end, sum=0;
    scanf("%d %d", &start, &end);
    for(int i = start; i <= end; i++){
        if(i>0){
            sum+=i;
        } else{
            return 0;
        }
    }
    printf("%d", sum);
}