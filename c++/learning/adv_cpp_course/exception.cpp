// exception handling and error example 1

#include <iostream>
#include <string>

void somethingGoingWrong(bool error1, bool error2){

    if(error1){
        throw 10;
    }
    if(error2){
        throw std::string("This is wrong dude.");
    }
}

void checkingProcess(bool error1, bool error2){
    somethingGoingWrong(error1,error2);
}

int main() {

    try{
        somethingGoingWrong(true,true);
    }
    catch(int err1){
        std::cout << "Error code: " << err1 << std::endl;
    }
    catch(std::string &err2){
        std::cout << err2 << std::endl;
    }
    
    return 0;
}