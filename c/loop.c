#include<stdio.h>
int main(){
    int i,a, sum;
    char b;
    sum = 0;
    scanf("%c",&b);
    if(b == '+')
    {
        printf("Enter minimum and maximum number \n");
        scanf("%d %d", &i, &a);
        for(; i<=a; i++){
            sum += i;
        }
        printf("\nresult = %d\n", sum);
    }
    else if(b == '-')
    {
        printf("Enter minimum and maximum number \n");
        scanf("%d %d", &i, &a);
        for(; i<=a; i++){
            sum -= i;
        }
        printf("\nresult = %d\n", sum);
    }
    else if(b == '*')
    {
        printf("Enter minimum and maximum number \n");
        scanf("%d %d", &i, &a);
        sum = 1;
        for(; i<=a; i++){
            sum *= i;
        }
        printf("\nresult = %d\n", sum);
    }
    else{
        printf("invalid operator");
    }
    return 0;
}