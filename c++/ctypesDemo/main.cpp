#include <iostream>

extern "C"
void printSum(int numA, int numB){
    int result {0};
    for(size_t i {0}; i < 100; ++i){
        result+=numA+numB;
    }
    std::cout << "The result is: " << result << std::endl;
}

extern "C"
void printMsg(){
    std::cout << "hi and welcome to this demo! " << std::endl;
}