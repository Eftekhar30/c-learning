#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int power();

int main(){
    
   printf("%d", power());
    return 0;
}

int power(){
    int a,b;
    scanf("%d", &a);
    scanf("%d", &b);
    int power = pow(a,b); 
    return power;
}
