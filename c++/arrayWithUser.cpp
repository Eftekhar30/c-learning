#include<iostream>
using namespace std;

int main(){

    string foods[5];
    int size = sizeof(foods)/sizeof(foods[0]);
    string temp;

    for(int i = 0; i<size; i++){
        cout<<"enter food names or 'q' to quit #"<< i+1<< ": ";
        getline(cin, temp);
        if(temp == "q"){
            break;
        }
        else{
            foods[i] = temp;
        }
    }
    cout<< "names are: "<<endl;

    for(int i = 0; !foods[i].empty(); i++){
        cout<<foods[i]<<endl;
    }

    return 0;
}