#include<stdio.h>
#include <string.h>

int main(){
    char name[100];
    char number[100];
    char address[100];
    char output[100];
    printf("enter your name:");
    gets(name);
    printf("enter your number:");
    gets(number);
    printf("enter your address:");
    gets(address);
    sprintf(output, "your name is %s", name);
    puts(output);
    sprintf(output, "your number is %s", number);
    puts(output);
    sprintf(output, "your address is %s", address);
    puts(output);
    
    return 0;
}