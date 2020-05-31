// Black jack game

#include "player.h"
#include "game_setup.h"
#include <iostream>

using namespace std;

int main () {
    cout << "Welcome to Blackjack!" << endl << endl << endl;
    // char input;

    Player p1;
    p1.set_name();
    p1.print_statement();
    // p1.change_money(-20);
    // p1.print_statement();

    // game loop
    // do {
    //     cout << "Enter your choice: " << endl;
    //     cin >> input;

    // } while (input != toupper('Q'));
    
    return 0;
}