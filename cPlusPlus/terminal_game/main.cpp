// making Tetris-style in the terminal using Ncurses library on Mac
// author: Marc-Antoine Lacroix

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

bool check_bottom(int size_y,Piece &p, int i, vector<int> vec_y, vector<int> vec_x) {
// checks to see if the object has reached the bottom of the board or collides with another underneath
// this function should be joined with another one

    int check {0};
    int y {p.get_y_shape()[i]};
    int x {p.get_x_shape()[i]};
    
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

void update_coordinates(vector<int> vec_y, vector<int> vec_x, int size_y, int size_x, Piece &p, int i,
                        int max_y, int max_x, int min_x, int key) {
// updates the position of the character in the game window 
// the if conditions insure you can't go overboard
// if conditions will have to be updated as objects get bigger and have more coordinates
    
    int y {p.get_y_shape()[i]};
    int x {p.get_x_shape()[i]};

    switch(key) {
        case 66:
            // down key
            if (max_y<size_y-2 && !collision(vec_y,vec_x,y+1,x)) {
                p.update_y_shape(1,i);
            } 
            break;
        case 67:
            // right key
            if (max_x<size_x-2 && !collision(vec_y,vec_x,y,max_x+1)) {
                p.update_x_shape(1,i);
            }
            break; 
        case 68:
            // left key
            if (min_x>1 && !collision(vec_y,vec_x,y,min_x-1)) {
                p.update_x_shape(-1,i);
            }
            break;
        case 'q':
            break;
    }
}

int main()
{   
    char selection {} ;
    
    do { 
        // this part to be rendered using ncurses instead
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        cout << "---***--- Welcome to Tetris! ---***---" << endl;
        cout << "Please enter your choice followed by ENTER:" << endl;
        cout << "Enter 's' to start a game" << endl;
        cout << "Enter 'q' to quit the game" << endl;
        cin >> selection;
        
        if (toupper(selection)=='S') {
            
            const int size_x {8};
            const int size_y {15};
            const int x_start {size_x/2};
            const int y_start {3};
            int x {x_start};
            int y {y_start};
            char ch1 [2] {"#"};
            char ch2 [2] {"*"};
            
            // S-shaped object
            Piece s_shape({y_start+1,y_start,y_start,y_start-1},
                            {x_start+1,x_start+1,x_start,x_start},
                            {y+1,y,y,y-1},{x+1,x+1,x,x});

            // L-shaped object
            Piece l_shape({y_start,y_start,y_start-1,y_start-2},
                            {x_start+1,x_start,x_start,x_start},
                            {y,y,y-1,y-2},{x+1,x,x,x});
            
            // Block-shaped object
            Piece b_shape({y_start-2,y_start-2,y_start-1,y_start-1},
                            {x_start+1,x_start,x_start+1,x_start},
                            {y-1,y-1,y,y},{x+1,x,x+1,x});
            
            Piece m_shape({y_start-3,y_start-2,y_start-1,y_start},
                            {x_start,x_start,x_start,x_start},
                            {y-3,y-2,y-1,y},{x,x,x,x});

            vector<Piece> fall_pieces {s_shape,l_shape,b_shape,m_shape};            
            // int j {rand()%4};
            int j {3}; // Pieces vector index initialization

            Objects blocks({size_y-1},{size_x-1}); // 

            // initializing game window
            init_ncurses();
            int key;
            WINDOW* game_window = newwin(size_y,size_x,y,x);
            refresh();
            clear();
            printw("Tetris - 'q' to quit - any arrow key to start\n");

            // game loop: 
            while((key=getch())!=113) { // 113 is code for "q" or "quit"
                wclear(game_window);
                
                vector<int> v1 {fall_pieces[j].get_y_shape()};
                vector<int> v2 {fall_pieces[j].get_x_shape()};
                int max_y {*max_element(v1.begin(),v1.end())};
                int max_x {*max_element(v2.begin(),v2.end())};
                int min_x {*min_element(v2.begin(),v2.end())};
                
                /* draw board */
                wborder(game_window,(int)'|',(int)'|',(int)' ',(int)'-',(int)'+',(int)'+',(int)'+',(int)'+');
                
                /* cursor position */
                for (size_t i = 0;i<size(fall_pieces[j].get_y_shape());++i){
                    wmove(game_window,fall_pieces[j].get_y_shape()[i],fall_pieces[j].get_x_shape()[i]);
                    wprintw(game_window,ch1); 
                }
                
                /* look for complete lines */
                blocks.erase_line(size_y,size_x); 
                
                /* print static objects */
                for (size_t i=0;i<size(blocks.get_y());++i) {
                    wmove(game_window,blocks.get_y()[i],blocks.get_x()[i]);
                    wprintw(game_window,ch2);
                }
                for (size_t i = 0;i<size(fall_pieces[j].get_y_shape());++i) {
                    update_coordinates(blocks.get_y(),blocks.get_x(),size_y,size_x,fall_pieces[j],i,max_y,max_x,min_x,key);
                }
                
                /* collision detection */
                for (size_t i = 0;i<size(fall_pieces[j].get_y_shape());++i) {
                    if (check_bottom(size_y,fall_pieces[j],i,blocks.get_y(),blocks.get_x())) {
                        // if true, push the positions of the piece to the objects board and reset its position
                        for (size_t i = 0;i<size(fall_pieces[j].get_y_shape());++i) {
                            blocks.push_x(fall_pieces[j].get_x_shape()[i]);
                            blocks.push_y(fall_pieces[j].get_y_shape()[i]);
                        }
                        // int next_j {rand()%4};
                        int next_j {3}; // to determine the next piece
                        for (size_t i = 0;i<size(fall_pieces[j].get_y_shape());++i) {
                            fall_pieces[j].reset_position(fall_pieces[next_j].get_y_init(),fall_pieces[next_j].get_x_init(),i);
                            wrefresh(game_window);
                        }
                        j = next_j;
                        break; 
                    } else {wrefresh(game_window);}
                }
            }
            delwin(game_window);
            blocks.reset({size_y-1},{size_x-1}); // resetting board 
            endwin();                  
        } else {
            cout << "\nPlease enter a valid choice." << endl;
        }

    } while (toupper(selection)!='Q');

    return 0;
}