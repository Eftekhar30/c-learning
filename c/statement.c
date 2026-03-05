#include<stdio.h>
int main(){
    int a;
    scanf("%d", &a);
    if(a>0){
        if("a%2==0"){
            printf("number is positive and even");
        }
        else{
            printf("number is positive and odd");
        }
    }
    else{
        if(a%2==0){
            printf("number is negative and even");
        }
        else{
            printf("number is negative and odd");
        }
    }
    return 0;
}