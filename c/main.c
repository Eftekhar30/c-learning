#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int power();

int main(){
    
   printf("%d", power());
    return 0;
}

int power(){
    int b;
    scanf("%d", &b);
    int power = pow(0,b); 
    return power;
}
