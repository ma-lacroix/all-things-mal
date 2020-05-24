// trying OOP

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>

class Player {

private:
    int age;
    std::string name;

public:
    int a;
    std::string n;
    std::string get_name();
    void set_name(std::string n);
    int get_age();
    void set_age(int a);

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
