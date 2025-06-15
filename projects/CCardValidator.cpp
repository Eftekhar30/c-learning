#include<iostream>
using namespace std;

int getDigit(const int number){
    return number%10 + (number/10 %10);
}

int sumOddDigits(const string cardnumber){
    int sum = 0;
    for(int i = cardnumber.size()-1; i >=0; i-=2){
        sum +=cardnumber[i] - '0';
    }
    return sum;
}

int sumEvenDigits(const string cardnumber){
    int sum = 0;
    for(int i = cardnumber.size()-2; i >=0; i-=2){
        sum +=getDigit((cardnumber[i]-'0') *2);
    }
    return sum;
}

int main(){
    string cardnumber;
    int result = 0;
    
    cout<<"enter a card number: ";
    cin>> cardnumber;
    result = sumEvenDigits(cardnumber) + sumOddDigits(cardnumber);
    if(result % 10 == 0){ 
        cout<< cardnumber << " is valid";
    }
    else{
        cout<< cardnumber << " is invalid.";
    }

    return 0;
}