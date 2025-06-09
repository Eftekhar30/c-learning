#include<iostream>
using namespace std;

int main(){
    float a,b; char c;
    cout<<"calculation: "<<endl;
    cin>>a>>c>>b;
    if(c == '+') 
        cout<< a+b<<endl;
    else if(c == '-') 
        cout<< a-b<<endl;
    else if(c == '*')
        cout<< a*b<<endl;
    else if(c == '/')
        cout<< a/b<<endl;
    else
        cout<<"invalid"<<endl;
    return 0;
}