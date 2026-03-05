#include<stdio.h>
void firstpage();
int main(){
    firstpage();
}
void firstpage(){
    int input;
    printf("bKash \n 1.Send Money \n 2.Send Money to Non-bKash User \n 3.Mobile Recharge\n 4.Payment\n 5.Cash Out\n 6.Pay Bill\n 7.Microfinance\n 8.Download bKash App\n 9.My bKash\n 10.Reset Pin\n");
    scanf("%d", &input);
    printf("%d\n", input);
}