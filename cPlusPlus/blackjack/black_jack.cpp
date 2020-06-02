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
    const string cards [13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
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
    const int card_values [13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};
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
    char choice;
    string menu_options [5] = {"B - Set a new bid","S - Start new game","C - Check current bid value",\
                                "M - Check token statement","Q - Quit game"};

    for (int i = 0;i < sizeof(menu_options)/sizeof(menu_options[0]); ++i) {
        cout << menu_options[i] << endl;
    }
    cout << "\nEnter your choice: ";
    cin >> choice;

    return toupper(choice);
}

int check_outcome(Player &one, Player &two) {
    int result;
    if (one.get_score() > two.get_score() && one.get_score() < 22 && two.get_score() < 22) {
        cout << "You win this round " << one.get_name() << endl;
        result = 1;
    }
    else if (one.get_score() < 22 && two.get_score() > 21) {
        cout << "You win this round " << one.get_name() << endl;
        result = 1;
    }
    else if (one.get_score() > 21 && two.get_score() > 21) {
        cout << "It's a tie " << one.get_name() << endl;
        result = 0;
    }
    else if (one.get_score() < 22 && two.get_score() < 21 && one.get_score()==two.get_score()) {
        cout << "It's a tie " << one.get_name() << endl;
        result = 0;
    }
    else {
        cout << "You lost this round " << one.get_name() << endl;
        result = -1;
    }
    return result;
}

void deal_card(int r,vector<string> deck, vector<int> deck_values, Player &p) {
// pulls a random card from the deck and adjust the player's score while removing the card from the deck
    int rand_index;
    rand_index = rand()%r;
    
    // display actual card
    cout << "***********" << endl;
    cout << "*" << deck[rand_index] <<  "*\n" << endl;
    
    p.set_score(deck_values[rand_index]);
    deck.erase(deck.begin()+rand_index); // removing card from deck
    deck_values.erase(deck_values.begin()+rand_index);
    --r; // decreasing random factor by 1
}

int black_jack(vector<string> deck, vector<int> deck_values, Player one, Player two) {

    srand (time(NULL)); // initializing rand
    int rand_index = 0;
    int result;
    char choice;

    int r = 52; // number of cards in the deck
    
    //* START GAME *//
    cout << "Let's play a game!" << endl << endl;
    // pull cards for the player
    deal_card(r,deck,deck_values,one);
    deal_card(r,deck,deck_values,one);
    cout << one.get_name() << " has a current score of: " << one.get_score() << endl;

    //pull cards for the dealer
    deal_card(r,deck,deck_values,two);
    deal_card(r,deck,deck_values,two);
    cout << two.get_name() << " has a current score of: " << two.get_score() << endl;

    do {cout << "would you like another card? (Y/N)" << endl;
        cin >> choice;
        if (toupper(choice) == 'Y') {
            deal_card(r,deck,deck_values,one);
        }
        cout << one.get_name() << " has a current score of: " << one.get_score() << endl;
    } while (choice == 'Y');
    
    while (two.get_score() < 17) {
        deal_card(r,deck,deck_values,two);
        cout << two.get_name() << " has a current score of: " << two.get_score() << endl;
    }

    result = check_outcome(one,two);
    
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
        else if (input == 'Q') {
            cout << "You're leaving?!? \n" << endl;
        }
        else {
            cout << "Invalid input." << endl;
        }
    } while (input != 'Q' || one.get_money()<=0);
    
    return 0;
}