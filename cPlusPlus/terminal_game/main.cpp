// trying out building a very simple game engine in terminal

#include <iostream> 
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

int keypress() {
  system ("/bin/stty raw");
  int c;
  system("/bin/stty -echo");
  c = getc(stdin);
  system("/bin/stty echo");
  system ("/bin/stty cooked");
  return c;
}

void refresh_screen() {
    // this_thread::sleep_until(chrono::system_clock::now() + 100000000ns);
    this_thread::sleep_until(chrono::system_clock::now());
    system("clear");
}

string concat_char(vector<int> p, string &c) {
// doesn't really work as expected - probably because of Unix terminal limitations
    string vert,horiz;
    for (int i=0;i<p[0];++i) {
        vert+="\n";
        horiz+=" ";
    }
    c=vert+horiz+c; // can't use += as we want the string to be at the end
    return c;
}

void update_position(int key, vector<int> &position){
    if (key==68) {
        // cout << "left key" << endl;
        position[0]-=1;
    }
    if (key==65) {
        // cout << "up key" << endl;
        position[1]+=1;
    }
    if (key==66) {
        // cout << "down key" << endl;
        position[1]-=1;
    }
    if (key==67) {
        // cout << "right key" << endl;
        position[0]+=1;
    }
}



int main() {
    refresh_screen();
    string dummy {"#"};
    vector<int> position {0,0};
    int key;
    
    do {
        refresh_screen();
        // cout << concat_char(position,dummy);
        cout << "\n\n x,y coord: " << position[0] << "," << position[1];
        refresh_screen();
        key = keypress();
        update_position(key,position);
        
    } while (key!=113); // "q for quit"
    
    refresh_screen();

    return 0;
}

