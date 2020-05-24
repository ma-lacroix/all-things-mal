// trying OOP

#include <iostream>
#include <string>
#include "player.h"

using namespace std;

int main() {
    int a = 15;
    string n = "Gabby";
    Player hero1;
    hero1.set_age(a);
    hero1.set_name(n);
    cout << "The player's age is: " << hero1.get_age() << endl;
    return 0;
}
