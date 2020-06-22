// making a Tetris-style game

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "objects.h"
#include "piece.h"

using namespace std;

void init_ncurses() {
/* ncurses initialisation stuff */
    initscr(); 
    noecho(); 
    cbreak();
    curs_set(0);
}

bool collision(vector<int> vec_y, vector<int> vec_x, int y, int x) {
// collision detection
    int check {0};
    for (size_t i=0;i<size(vec_y);++i) {
        if(y == vec_y[i] && x == vec_x[i]) {
            check=1;
        }
    }
    if(check==1) {
        return true;
    }
    else {return false;}
}   

bool check_bottom(int size_y,int y, int x, vector<int> vec_y, vector<int> vec_x) {
// checks to see if the object has reached the bottom of the board or collides with another underneath
// this function should be joined with another one

    int check {0};
    for (size_t i=0;i<size(vec_y);++i) {
        if((y+1 == vec_y[i] && x == vec_x[i]) || y+1 == size_y-1) {
            check=1;
        }
    }
    if(check==1) {
        return true;
    }
    else {return false;} 
}

void update_coordinates(vector<int> vec_y, vector<int> vec_x, int size_y, int size_x, int &y, int &x, int key) {
// updates the position of the character in the game window 
// the if conditions insure you can't go overboard
// if conditions will have to be updated as objects get bigger and have more coordinates
    
    switch(key) {
        case 65:
            // up key
            y-=1;
            // if (y>1 && !collision(vec_y,vec_x,y-1,x)) {
            //     y-=1;
            // }
            break;
        case 66:
            // down key
            if (y<size_y-2 && !collision(vec_y,vec_x,y+1,x)) {
                y+=1;
            } 
            break;
        case 67:
            // right key
            if (x<size_x-2 && !collision(vec_y,vec_x,y,x+1)) {x+=1;}
            break; 
        case 68:
            // left key
            if (x>1 && !collision(vec_y,vec_x,y,x-1)) {x-=1;}
            break;
        case 'q':
            break;
    }
}

int main()
{
    int key;
    int size_x {17};
    int size_y {15};
    int x_start {1};
    int y_start {3};
    int x {x_start};
    int y {y_start};
    // trying out a L-shaped object
    // **** to be implemented in class "Piece" **** //
    vector<int> y_init {y_start,y_start,y_start-1,y_start-2};
    vector<int> x_init {x_start+1,x_start,x_start,x_start};
    vector<int> y_shape {y,y,y-1,y-2};
    vector<int> x_shape {x+1,x,x,x};
    char ch1 [2] {"#"};
    char ch2 [2] {"@"};

    // Object b1(,size_x-2);

    Objects blocks({size_y-2},{size_x-2}); // won't work if no blocks are pre-defined

    // initializing stuff:
    init_ncurses();
    WINDOW* game_window = newwin(size_y,size_x,y,x);
    refresh();
    printw("Press any arrow key to start");
    getch();
    clear();

    // game loop: 
    printw("Tetris in the making\n");

    while((key=getch())!=113) { // 113 is code for "q" or "quit"
        wclear(game_window);
        // draw board
        wborder(game_window,(int)'|',(int)'|',(int)' ',(int)'-',(int)'+',(int)'+',(int)'+',(int)'+');
        // cursor position
        for (size_t i = 0;i<size(y_shape);++i){
            wmove(game_window,y_shape[i],x_shape[i]);
            wprintw(game_window,ch1); 
        }
        //print static objects
        for (size_t i=0;i<size(blocks.get_y());++i) {
            wmove(game_window,blocks.get_y()[i],blocks.get_x()[i]);
            wprintw(game_window,ch2);
        }
        for (size_t i = 0;i<size(y_shape);++i) {
            update_coordinates(blocks.get_y(),blocks.get_x(),size_y,size_x,y_shape[i],x_shape[i],key);
        }
        for (size_t i = 0;i<size(y_shape);++i) {
            if (check_bottom(size_y,y_shape[i],x_shape[i],blocks.get_y(),blocks.get_x())) {
                for (size_t i = 0;i<size(y_shape);++i) {
                    blocks.push_x(x_shape[i]);
                    blocks.push_y(y_shape[i]);
                    x_shape[i]=x_init[i];
                    y_shape[i]=y_init[i];
                    wrefresh(game_window);
                } 
            } else {wrefresh(game_window);}
        }
    }
    delwin(game_window);
    endwin();                  

    return 0;
}