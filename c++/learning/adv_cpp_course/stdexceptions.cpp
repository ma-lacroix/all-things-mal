//exception handling example 2 - std::bad_alloc

#include <iostream>
#include <string>

class allocatemem {
private:
    int mem_amount;
public:
    allocatemem(int mem_amount){
        char *mem = new char[mem_amount];
        delete[] mem;
    }
    void print_amount(){std::cout << mem_amount << std::endl;};
};

int main() {

    try{
        allocatemem memo(1000000000000000000);
        memo.print_amount();
    }
    catch(std::bad_alloc &err){
        std::cout << "Memory error: " << err.what() << std::endl;
    }

    return 0;

}