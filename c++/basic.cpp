#include<iostream>
using namespace std;

class rectangle {
    int height;
    int width;
public:
    void set(int h, int w);
    int area();
};
inline int rectangle::area(){
    return height *width;
}
void rectangle::set(int h, int w){
    height = h;
    width = w;
    
}
int main()
{
    rectangle obj;
    int h,w;
    cin>>h>>w;
    obj.set(h,w);
    cout<< "Area is = "<<obj.area()<<endl;

    return 0;
}