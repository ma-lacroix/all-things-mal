// Header for blackjack game

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <string>

class Player {

private:
    std::string p_name;
    int p_money;

public:
    Player();
    Player(const Player &s);    
    int get_money() {return p_money;};
    std::string get_name() {return p_name;};
    void set_name();
    void change_money(int v);
    void print_statement();
};

Player::Player()
    :p_name("J"),p_money(100) {}

Player::Player(const Player &source)
    :p_name(source.p_name),p_money(source.p_money) {
        std::cout << "Calling class constructor copier" << std::endl;
    }

void Player::set_name() {
    std::cout << "Please enter your name: " << std::endl;
    std::cin >> p_name;
}

void Player::change_money(int value) {
    p_money+=value;
}

void Player::print_statement() {
    std::cout << get_name() << ", you currently have " << get_money() << " tokens." << std::endl;
}

#endif