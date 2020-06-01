// Header for blackjack game

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <string>

class Player {

private:
    std::string p_name;
    int p_money;
    int p_score;
    int p_bid;

public:
    Player();
    Player(const Player &s);  
    int get_money() {return p_money;};
    int get_score() {return p_score;};
    int get_bid() {return p_bid;};
    std::string get_name() {return p_name;};
    void set_name();
    void change_money(int v);
    void print_statement();
    void set_score(int s);
    void set_bid();
    void check_bid();
};

Player::Player()
    :p_name("Dealer"),p_money(100),p_score(0) {}

Player::Player(const Player &source)
    :p_name(source.p_name),p_money(source.p_money),p_score(source.p_score) {}

void Player::set_name() {
    std::cout << "Please enter your name: " << std::endl;
    std::cin >> p_name;
}

void Player::change_money(int value) {
    p_money+=value;
}

void Player::print_statement() {
    std::cout << get_name() << ", you currently have " << get_money() << " tokens." << std::endl << std::endl;
}

void Player::set_score(int value) {
    p_score+=value;
}

void Player::set_bid() {
    std::cout << "Enter your bid value: ";
    std::cin >> p_bid;
    if (p_bid > get_money()) {
        std::cout << "Bid value exceeds the number of tokens you have." << std::endl;
        set_bid();
    }
    else {
        std::cout << "Bid placed. " << std::endl;
    }
}

void Player::check_bid() {
    std::cout << get_name() << ", you set your bid to: " << get_bid() << " tokens." << std::endl << std::endl;
}

#endif