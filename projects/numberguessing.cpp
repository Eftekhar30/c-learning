#include<iostream>
#include<ctime>
using namespace std;

int main(){
    int guess;
    int number;
    int tries=0;

    srand(time(NULL));
    number = (rand() %100) +1;
    cout<< "******* Number Guessing game *******\n";

    do{
        cout<< "Enter a number (1-100): ";
        cin>>guess;
        tries++;
        if(guess > number){
            cout<<"go low \n";
        }
        else if(guess < number){
            cout<< "go high\n";
        }
        else{
            cout<< "correct! you tried "<< tries<< "times";
        }


    }while(guess != number);

    return 0;
}