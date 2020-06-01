// Black jack game

#include "player.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>  

using namespace std;

vector<string> create_deck() {
// creates the deck of cards
    const string suits [4] = {"_hearts","_spades","_diamonds","_clubs"};
    const string cards [14] = {"1","2","3","4","5","6","7","8","9","10","J","Q","K","A"};
    int s_suits = sizeof(suits)/sizeof(suits[0]);
    int s_cards = sizeof(cards)/sizeof(cards[0]);
    vector<string> deck;
    for (size_t i = 0; i < s_suits; ++i) {
        for (size_t j = 0; j < s_cards ; ++j) {
            deck.push_back(cards[j]+suits[i]);
        }
    }
    return deck;
}

vector<int> card_values() {
// creates a vector with card values - kind of repetitive with previous function
    const int card_values [14] = {1,2,3,4,5,6,7,8,9,10,10,10,10,11};
    int s_values = sizeof(card_values)/sizeof(card_values[0]);
    vector<int> deck_values;
    for (int i=0;i < 4; ++i) {
        for (size_t j=0;j<s_values;++j) {
            deck_values.push_back(card_values[j]);
        }
    }
    return deck_values;
}

char display_options() {
// this function displays the menu options
    
    string menu_options [5] = {"B - Set a new bid","S - Start new game","C - Check current bid value",\
                                "M - Check token statement","Q - Quit game"};

    for (int i = 0;i < sizeof(menu_options)/sizeof(menu_options[0]); ++i) {
        cout << menu_options[i] << endl;
    }
    char choice;
    cin >> choice;

    return toupper(choice);
}

char deal_new_card() {
    char choice;
    cout << "Would you like another card? (Y/N)" << endl;
    cin >> choice;
    return toupper(choice);
}

int black_jack(vector<string> deck, vector<int> deck_values, Player one, Player two) {

// massive WIP !!!!! - need to create proper game loop and printing functions in terminal

    srand (time(NULL));
    int rand_index = 0;
    int result;
    char choice;

        
    int r = 58;
    
    // pull cards for the player
    rand_index = rand()%r;
    cout << deck[rand_index] << endl;
    one.set_score(deck_values[rand_index]);
    deck.erase(deck.begin()+rand_index); // removing card from deck
    deck_values.erase(deck_values.begin()+rand_index);
    --r;
    rand_index = rand()%r;
    cout << deck[rand_index] << endl;
    one.set_score(deck_values[rand_index]);
    deck.erase(deck.begin()+rand_index); // removing card from deck
    deck_values.erase(deck_values.begin()+rand_index);
    --r;
    cout << one.get_name() << " has a current score of: " << one.get_score() << endl;

    //pull cards for the dealer
    rand_index = rand()%r;
    cout << deck[rand_index] << endl;
    two.set_score(deck_values[rand_index]);
    deck.erase(deck.begin()+rand_index); // removing card from deck
    deck_values.erase(deck_values.begin()+rand_index);
    --r;
    rand_index = rand()%r;
    cout << deck[rand_index] << endl;
    two.set_score(deck_values[rand_index]);
    deck.erase(deck.begin()+rand_index); // removing card from deck
    deck_values.erase(deck_values.begin()+rand_index);
    --r;
    cout << two.get_name() << " has a current score of: " << two.get_score() << endl;

    choice = deal_new_card();
    if (choice == 'Y') {
        rand_index = rand()%r;
        cout << deck[rand_index] << endl;
        one.set_score(deck_values[rand_index]);
        deck.erase(deck.begin()+rand_index); // removing card from deck
        deck_values.erase(deck_values.begin()+rand_index);
        --r;
        cout << one.get_name() << " has a current score of: " << one.get_score() << endl;
    }
    if (two.get_score() < 17) {
        rand_index = rand()%r;
        cout << deck[rand_index] << endl;
        two.set_score(deck_values[rand_index]);
        deck.erase(deck.begin()+rand_index); // removing card from deck
        deck_values.erase(deck_values.begin()+rand_index);
        --r;
        cout << two.get_name() << " has a current score of: " << two.get_score() << endl;
    }

    if (one.get_score() > two.get_score() && one.get_score() < 22) {
        cout << "You win this round " << one.get_name() << endl;
        result = 1;
    } 
    else {
        cout << "You lost this round " << one.get_name() << endl;
        result = -1;
    }
    
    return result;
}

int main () {
    
    vector<string> deck;
    vector<int> deck_values;
    deck = create_deck();
    deck_values = card_values();
    char input;
    int result;

    Player one;
    Player two;
    one.set_name();

    cout << "Welcome to Blackjack!" << endl << endl << endl;
    //game loop
    do { 
        cout << "What will you do next? " << endl << endl;
        input = display_options();
        if (input == 'S') {
            result=black_jack(deck,deck_values,one,two);
            one.change_money(one.get_bid()*result);
        }
        else if (input == 'B') {
            one.set_bid();
        }
        else if (input == 'C') {
            one.check_bid();
        }
        else if (input == 'M') {
            one.print_statement();
        }
        else {
            cout << "Invalid input." << endl;
        }
    } while (input != 'Q');
    
    return 0;
}