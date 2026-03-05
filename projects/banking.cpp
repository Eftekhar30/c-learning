#include<iostream>
#include<iomanip>
using namespace std;

void ShowBalance(double balance){
    cout<< "Your Balance is: "<<setprecision(2)<<fixed<< balance<<endl;
}

double deposit(){
    double amount = 0;
    cout<<"Enter your deposit: ";
    cin>>amount;

    if(amount>0){
        return amount;
    }
    else{
        cout<<"invalid deposit!\n";
        return 0;
    }
}

double withdraw(double balance){
    double amount =0;
    cout<< "ENter your withdraw amount: ";
    cin>>amount;

    if(amount <0){
        cout<< "not a valid amount\n";
        return 0;
    }
    else if(amount>balance){
        cout<<"insufficiant funds!\n";
        return 0;
    }
    else{
        return amount;
    }
}

int main(){
    double balance= 0;
    int choice = 0;

    do{
        cout<<"*********** BANK SYSTEM ***********\n";
        cout<<"1. Check Balance\n";
        cout<<"2. deposit\n";
        cout<<"3. withdraw\n";
        cout<<"4. exit\n";
        cout<<"***********************************\n";
        cout<<"enter your choice: \n";
        cin>>choice;

        cin.clear();
        fflush(stdin);

        switch(choice){
            case 1: ShowBalance(balance);
                break;
            case 2: balance += deposit();
                    ShowBalance(balance);
                break;
            case 3: balance -= withdraw(balance);
                    ShowBalance(balance);
                break;
            case 4: cout<<"Thanks for visiting!\n";
                break;
            default: cout<<"invalid choice\n";
        }
    }while(choice != 4);

    

    return 0;
}