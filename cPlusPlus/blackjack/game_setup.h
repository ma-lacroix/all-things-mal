// Game rules and set-up for blackjack game

#ifndef _GAME_SETUP_H
#define _GAME_SETUP_H
#include <iostream>
#include <string>
#include <vector>



class Game {
public:
    Game();
    std::string cards [14];
    std::string suits [4];
    void set_cards();
    void set_suits();
};

void Game::set_cards() {
    cards [14] = {"1","2","3","4","5","6","7","8","9","10","J","Q","K","A"};
}

void Game::set_suits() {
    suits [4] = {"H","S","D","C"};
}

#endif