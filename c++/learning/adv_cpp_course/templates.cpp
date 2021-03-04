// trying out class templates

#include <iostream>
#include <string>

template<typename T>
class someTclass{

private:
    T object1;
    T object2;
    int num1;

public:
    someTclass(T o1, T o2, int n1):
        object1(o1),object2(o2),num1(n1){
            std::cout << "constructor called" << std::endl;
        }
    
    ~someTclass(){}
    
    friend std::ostream &operator<<(std::ostream &out, const someTclass &o){
        std::cout << o.object1 << ", " << o.object2 << ", " << o.num1 << std::endl;
        return out;
    }
};

int main() {
    someTclass<std::string> class1("Hi","There",3);
    std::cout << class1 << std::endl;
    return 0;
}