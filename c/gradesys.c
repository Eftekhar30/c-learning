#include<stdio.h>

void grade_cheacking_menu();
void grade_functions();
void grade();


int main(){
    grade_cheacking_menu();
    grade_functions();
    grade();
}

void grade_cheacking_menu(){
    
    printf("*--------------------------------------*\n");
    printf("*                                      *\n");
    printf("*         Welcome to the portal        *\n");
    printf("*                                      *\n");
    printf("*--------------------------------------*\n");
    printf("*                                      *\n");
    printf("* 1. grade check                       *\n");
    printf("*                                      *\n");
    printf("*--------------------------------------*\n");
    
}

void grade_functions(){
    int a;
    printf("Enter: ");
    scanf("%d", &a);
}

void grade(){
    int a;
    printf("enter your grade: ");
    scanf("%d", &a);
    if(a<=39){
        printf("fail");
    } else if(a>=80 && a<=100){
        printf("A+");
    } else if(a>=70 && a<80){
        printf("A");
    } else if(a>=60 && a<70){
        printf("B");
    } else if(a>=50 && a<60){
        printf("C");
    } else if(a>= 40 && a<50){
        printf("D");
    } else{
        printf("invalid");
    }
}