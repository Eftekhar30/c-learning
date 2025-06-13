#include<iostream>
using namespace std;

static int count = 0;

void students(char names[][80]);
void list(char names[][80]);

int main(){
    int choice = 0;
    char names[100][80] = {{0}};
    do{
    cout<<"*****************************************\n";
    cout<<"*          student information          *\n";
    cout<<"*****************************************\n";
    cout<<"* 1. Student Names.                     *\n";
    cout<<"* 2. List.                              *\n";
    cout<<"* 3. exit.                              *\n";
    cout<<"*****************************************\n";
    cout<<"enter your choice: ";
    cin>>choice;

    switch(choice){
            case 1: 
                students(names);
                break;
            case 2:
                list(names);
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }

    }while(choice !=3);
    return 0;
}

void students(char names[][80]){
    cout << "How many student names do you want to enter? ";
    int n;
    cin >> n;
    cin.ignore();
    
    if(count + n > 100){
        cout << "Cannot add more students. Maximum limit is 100.\n";
        return;
    }

    for(int i = 0; i < n; i++){
        cout << "Enter name for student " << (count + i + 1) << ": ";
        cin.getline(names[count + i], 80);
    }
    count += n;
}

void list(char names[][80]){
    cout << "\nList of Students:\n";
    cout << "----------------\n";
    
    if(count == 0){
        cout << "No students in the list yet!\n";
    }
    else{
        for(int i = 0; i < count; i++){
            cout << (i + 1) << ". " << names[i] << endl;
        }
    }
    cout << "----------------\n";
    cout<< "\nPress Enter to continue...";
    cin.ignore(10000, '\n');
    cin.get();
    system("cls");
}