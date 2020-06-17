// testing ncurses library

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

using namespace std;

void update_coordinates(int size_y, int size_x, int &y, int &x, int key) {
// updates the position of the character in the game window 
// the if conditions insure you can't go overboard
// if conditions will have to be updated as objects get bigger and have more coordinates
    switch(key) {
        case 65:
            // up key
            if (y>1) {y-=1;}
            break;
        case 66:
            // down key
            if (y<size_y-2) {y+=1;} 
            break;
        case 67:
            // right key
            if (x<size_x-2) {x+=1;}
            break; 
        case 68:
            // left key
            if (x>1) {x-=1;}
            break;
        case 'q':
            break;
    }
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
    char ch [2] {"#"};

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
        wborder(game_window,(int)'|',(int)'|',(int)'-',(int)'-',(int)'+',(int)'+',(int)'+',(int)'+');
        wmove(game_window,y,x);
        wprintw(game_window,ch);
        
        update_coordinates(size_y,size_x,y,x,key);
        wrefresh(game_window);
    }
    delwin(game_window);
    endwin();                  

    return 0;
}