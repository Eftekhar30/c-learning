#include<iostream>
using namespace std;

int main(){

    string questions[] = {
        "1. Download CSGO from which platform?: ",
        "2. Owner of Steam?: ",
        "3. First black rank?: ",
        "4. Top rank?: "
    };
    string options[][4] = {
        {"A. Epic Games", "B. Ubisoft", "C. Steam", "D. Riot Games"},
        {"A. Putin", "B. Modi", "C. Xia", "D. Gaben"},
        {"A. DMG", "B. SE", "C. MGE", "D. GN2"},
        {"A. LE", "B. GE", "C. LEM", "D. DMG"}
    };

    char anskey[]={'C', 'D', 'A', 'B'};

    int size = sizeof(questions)/sizeof(questions[0]);
    char guess;
    int score = 0;

    for(int i = 0; i<size; i++){
        cout<<"*********************************\n";
        cout<<questions[i]<<endl;
        cout<<"*********************************\n";
        for(int j = 0; j < sizeof(options[i])/sizeof(options[i][0]);j++){
            cout<< options[i][j]<<endl;
        }

        cin>>guess;
        guess = toupper(guess);

        if(guess == anskey[i]){
            cout<<"correct "<<endl;
            score++;
        }
        else{
            cout<<"WRONG!"<<endl;
            cout<< "Answer: "<< anskey[i]<<endl;
        }

    }
    
    cout<<"*********************************\n";
    cout<<"*            RESULTS            *\n";
    cout<<"*********************************\n";
    cout<<"CORRECT GUESSES: "<<score<<endl;
    cout<<"# of QUESTIONS: "<<size<<endl;
    cout<<"SCORE: "<<(score/(double)size)*100<<"%";

    return 0;
}