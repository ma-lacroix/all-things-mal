// a simple OOP program in which I can enter some game info and display them using a menu

#include <iostream>
#include <string>
#include <vector>
#include "inventory.h"

using namespace std;

char display_options() {
// this function displays the menu options
    
    string menu_options [3] = {"A - Add games","P - Print games","Q - Quit"};

    for (int i = 0;i < sizeof(menu_options)/sizeof(menu_options[0]); ++i) {
        cout << menu_options[i] << endl;
    }
    char choice;
    cin >> choice;

    return choice;
}

int main() {

    vector<string> name,type;
    vector<int> ind,year_release,score;
    char selection ='E';
    Game example;

    cout << "Welcome to your game inventory management system! " << endl;

    do {selection = toupper(display_options());
        if (selection == 'A') {
            example.add_new_game(ind,name,type,year_release,score);
        }
        else if (selection == 'P') {
            example.print_games(ind,name,type,year_release,score);
        }
        else if (selection == 'Q') {
            cout << "We're done here!" << endl;
        }
        else {
            cout << "Please enter a valid choice from the menu" << endl;
        }
    } while (selection != 'Q');

    return 0;
}
