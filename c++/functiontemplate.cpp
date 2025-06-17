#include<iostream>
using namespace std;
template <typename T, typename U>

auto max(T x, U y){
    return (x > y) ? x : y;
}

int main(){

    cout<<max( 8.3, 2)<<endl;

    return 0;
}
