#include<iostream>
#include<cctype>
using namespace std;

int main(){
    char *pGrades = NULL;
    int size;

    cout << "How many grades do you want to input: ";
    cin >> size;

    pGrades = new char[size];

    for(int i = 0; i < size; i++){
        cout << "Enter grade #" << (i+1) << ": ";
        cin >> pGrades[i];
        pGrades[i] = toupper(pGrades[i]);
    }

    cout << "\nYour grades are:\n";
    for(int i = 0; i < size; i++){
        cout << "Grade #" << (i+1) << ": " << pGrades[i] << endl;
    }

    delete[] pGrades;
    pGrades = NULL;

    return 0;
}