#include<stdio.h>

int main(){
    int b,c,sum;
    char a;
    scanf("%d %c %d", &b, &a,  &c);
    
    if(a == '+'){
        sum= b+c;
        printf("%d", sum);
    }
    else if(a == '-'){
        sum= b-c;
        printf("%d", sum);
    }
    else if(a == '*'){
        sum= b*c;
        printf("%d", sum);
    }
    else if(a == '/'){
        sum= b/c;
        printf("%d", sum);
    }
    return 0;
}