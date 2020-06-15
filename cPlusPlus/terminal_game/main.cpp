// testing ncurses library

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

using namespace std;

void update_coordinates(int &y, int &x, int key) {
    switch(key) {
        case 65:
            y-=1; 
            break;
        case 66:
            // down key
            y+=1; 
            break;
        case 67:
            // right key
            x+=1;
            break; 
        case 68:
            // left key
            x-=1;
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
    int x {1};
    int y {1};
    char ch [2] {"#"};

    // initializing stuff:
    init_ncurses();
    WINDOW* game_window = newwin(15,20,y,x);
    refresh();
    printw("Press any arrow key to start");
    getch();
    clear();

    // game starts here: 
    printw("This is supposed to be Tetris");
    while((key=getch())!=113) { // 113 is code for "q" or "quit"
        wclear(game_window);
        wborder(game_window,(int)'|',(int)'|',(int)'-',(int)'-',(int)'+',(int)'+',(int)'+',(int)'+');
        wmove(game_window,y,x);
        wprintw(game_window,ch);
        update_coordinates(y,x,key);
        wrefresh(game_window);
    }
    // delwin(game_window);
    endwin();                  

    return 0;
}