// trying OOP

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include <vector>

class Game {

private:
    vector<std::string> index;
    vector<std::string> name;
    vector<std::string> type;
    vector<int> year_release;    
    vector<int> score;

public:
    
    void add_new_game();
    void print_games();
    
    
    

};

int a;
std::string n;

std::string Player::get_name() {
    return name;
}

void Player::set_name(std::string n) {
    name = n;
}

int Player::get_age() {
    return age;
}
void Player::set_age(int a) {
    age = a;
}

#endif
