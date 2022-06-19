#include "cc.hpp"
#include <iostream>
#include <string>


creditCard::creditCard(std::string new_number) {
    if(new_number.size()==10){
        std::cout << "Valid CC number" << std::endl;
        this->cc_number = new_number;
    } else {
        std::cout << "Invalid CC number" << std::endl;
        this->cc_number = "XXXXXXXXXX";
    }
    this->status = true;
};
creditCard::~creditCard() {
    std::cout << "cc deleted" << std::endl;
};
bool creditCard::checkStatus() {
    // implement Luhn algorithm
    return false;
};
std::string creditCard::getCC() {
    return cc_number.substr(0,3);
}
bool creditCard::getStatus() {
    return status;
}
