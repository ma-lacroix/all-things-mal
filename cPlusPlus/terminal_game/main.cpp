// trying out building a very simple game engine in terminal

#include <iostream> 
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

string key_input() {
    char ch;
    system ("/bin/stty raw");
    ch=getchar();
        if(ch==65) {return "up";}
        else if(ch==66) {return "down";}
        else if(ch==67) {return "right";}
        else if(ch==68) {return "left";}
        else {return "nothing";}
    system ("/bin/stty cooked");
    }

void adjust_position(vector<int> &position) {
    string new_pos = key_input();
    if (new_pos=="up") {position[0]-1;}
    else if (new_pos=="down") {position[0]+1;}
    else if (new_pos=="left") {position[1]-1;}
    else if (new_pos=="right") {position[1]+1;}
}

vector<vector<string> > vect1{
        {"#"},{"#"},{"#"}
        };

void refresh_screen() {
    this_thread::sleep_until(chrono::system_clock::now() + 100000000ns);
    system("clear");
}


int main() {
    refresh_screen();
    vector<int> position {0,0};
    adjust_position(position);
    // while(1) {
    //     for (size_t i=0;i<size(vect1);++i) {
    //     cout << vect1[i][0] << endl;
    //     }
    // refresh_screen();
    // }
    return 0;
}

