#include<iostream>
#include<ctime>
using namespace std;

char User();
char Computer();
void showChoice(char choice);
void winner(char player, char computer);

int main(){
    char p, c;
    p = User();
    cout<<"your choice is: ";
    showChoice(p);

    c = Computer();
    cout<<"Computer's choice is: ";
    showChoice(c);

    winner(p,c);

    return 0;
}

char User(){
    char player;
    do{
        cout<<"****************************\n";
        cout<<"Rock-Paper-Scissors game\n";
        cout<<"choose one of the followings\n";
        cout<<"****************************\n";
        cout<< "'r' for rock\n";
        cout<< "'p' for paper"<<endl;
        cout<< "'s' for scissors\n";
        cin>>player;
    }while(player != 'r' && player != 'p' && player != 's' && player != 'R' && player != 'P' && player != 'S');
    return player;
}
char Computer(){
    srand(time(0));
    int num = rand() % 3 + 1;
    switch(num){
        case 1: return 'r';
        case 2: return 'p';
        case 3: return 's';
    }
}
void showChoice(char choice){
    switch(choice){
        case 'r': cout<< "your choice is: Rock\n";
                    break;
        case 'R': cout<< "your choice is: Rock\n";
                    break;
        case 'p': cout<< "your choice is: Paper\n";
                    break;
        case 'P': cout<< "your choice is: Paper\n";
                    break;
        case 's': cout<< "your choice is: Scissors\n";
                    break;
        case 'S': cout<< "your choice is: Scissors\n";
                    break;
        
    }
}
void winner(char player, char computer){
    switch(player){
        case 'r':if(computer == 'r'){
                    cout<< "TIE!";
                 }
                else if(computer == 'p'){
                    cout<< "LOSE!";
                 }
                else{
                    cout<< "WIN!";
                 }
            break;
        case 'p':if(computer == 'r'){
                    cout<< "WIN!";
                 }
                else if(computer == 'p'){
                    cout<< "TIE!";
                 }
                else{
                    cout<< "LOSE!";
                 }
            break;
        case 's':if(computer == 'r'){
                    cout<< "LOSE!";
                 }
                else if(computer == 'p'){
                    cout<< "WIN!";
                 }
                else{
                    cout<< "DRAW!";
                 }
            break;
    }

}