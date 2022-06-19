#include <iostream>
#include <vector>
#include <string>
#include "cc.hpp"


int main(int argc, char **argv) {
    
    std::vector<creditCard*> cards;
    
    for (size_t i = 1; i < argc; ++i) {
        std::string some_card = static_cast<std::string>(argv[i]);
        cards.push_back(new creditCard(some_card));
    }
    
    return 0;
}