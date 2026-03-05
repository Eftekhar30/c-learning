#include<stdio.h>
int main(){
    int a;
    printf("subject number:");
    scanf("%d", &a);

    if(a<=39){
        printf("fail");
    } else if(a>=80 && a<=100){
        printf("A+");
    } else if(a>=70 && a<80){
        printf("A");
    } else if(a>=60 && a<70){
        printf("A-");
    } else if(a>=50 && a<60){
        printf("B");
    } else if(a>= 40 && a<50){
        printf("C");
    } else{
        printf("F");
    }
}