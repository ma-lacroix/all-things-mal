// testing ncurses library

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "objects.h"

using namespace std;

bool collision(vector<Object*> vec, int y, int x) {
    int check {0};
    for (auto v : vec) {
        if(y == v->get_y() && x == v->get_x()) {
            check=1;
        }
    }
    if(check==1) {return true;}
    else {return false;}
}   

void update_coordinates(vector<Object*> vec, int size_y, int size_x, int &y, int &x, int key) {
// updates the position of the character in the game window 
// the if conditions insure you can't go overboard
// if conditions will have to be updated as objects get bigger and have more coordinates
    switch(key) {
        case 65:
            // up key
            if (y>1 && !collision(vec,y-1,x)) {
                y-=1;
            }
            break;
        case 66:
            // down key
            if (y<size_y-2 && !collision(vec,y+1,x)) {
                y+=1;
            } 
            break;
        case 67:
            // right key
            if (x<size_x-2 && !collision(vec,y,x+1)) {x+=1;}
            break; 
        case 68:
            // left key
            if (x>1 && !collision(vec,y,x-1)) {x-=1;}
            break;
        case 'q':
            break;
    }
}

void add_objects() {
// add function that can print objects in the window
}


void init_ncurses() {
/* ncurses initialisation stuff */
    initscr(); 
    noecho(); 
    cbreak();
    curs_set(0);
}

int main()
{
    int key;
    int size_x {17};
    int size_y {16};
    int x {1};
    int y {1};
    char ch1 [2] {'#'};
    char ch2 [2] {'@'};

    // Objects around the board (to be automated)
    Object b1(size_y-2,size_x-2);
    Object b2(size_y-2,size_x-3);
    Object b3(size_y-2,size_x-4);
    Object b4(size_y-2,size_x-5);
    Object b5(size_y-10,size_x-13);
    vector<Object*> objs {&b1,&b2,&b3,&b4,&b5};

    // initializing stuff:
    init_ncurses();
    WINDOW* game_window = newwin(size_y,size_x,y,x);
    refresh();
    printw("Press any arrow key to start");
    getch();
    clear();

    // game starts here: 
    printw("Tetris in the making\n");
    while((key=getch())!=113) { // 113 is code for "q" or "quit"
        wclear(game_window);
        // draw board
        wborder(game_window,(int)'|',(int)'|',(int)'-',(int)'-',(int)'+',(int)'+',(int)'+',(int)'+');
        // cursor position
        wmove(game_window,y,x);
        wprintw(game_window,ch1); 
        //print static objects
        for (auto obj : objs) {
            wmove(game_window,obj->get_y(),obj->get_x());
            wprintw(game_window,ch2);
        }
        update_coordinates(objs,size_y,size_x,y,x,key);
        wrefresh(game_window);
    }
    delwin(game_window);
    endwin();                  

    return 0;
}