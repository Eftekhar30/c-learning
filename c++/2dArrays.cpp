#include<iostream>
using namespace std;

int main(){
    string games [][3]={{"csgo,", "cs2,", "tf2"},
                        {"valorant,", "league of legends,", "cod"},
                        {"rdr2,", "r6 seige,", "dota"}};
    int row = sizeof(games)/sizeof(games[0]);
    int columns= sizeof(games[0])/sizeof(games[0][0]);

    for(int i = 0; i<row;i++){
        for(int j = 0; j< columns; j++){
            cout<< games[i][j]<< " ";
        }
        cout<<endl;
    }

    return 0;
}