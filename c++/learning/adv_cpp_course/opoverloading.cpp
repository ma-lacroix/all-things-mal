#include <iostream>

class Simple{
private: 
    int num1;
    int num2;
public:
    Simple()
        // num1(0),num2(0)
        {
        this->num1 = 0;
        this->num2 = 0;
        std::cout << "Default class constructor called" << std::endl;
        }
    Simple(int anum, int bnum)
        // num1(anum),num2(bnum)
        {
        this->num1 = anum;
        this->num2 = bnum;
        std::cout << "Class constructor called" << std::endl;
        }
    ~Simple(){};
    
    const Simple &operator=(const Simple &other){
        std::cout << "Assignement operator running" << std::endl;
        num1 = other.num1;
        num2 = other.num2;
        return *this;
    }
    friend void print(Simple&);

    friend std::ostream &operator<<(std::ostream &out, const Simple &other){
        std::cout << other.num1 << " " << other.num2 << std::endl;
        return out;
    }
};

void print(Simple &simp){
        std::cout << simp.num1 << " " << simp.num2 << std::endl;
    }

int main(){
    Simple ex1(12,43);
    print(ex1);
    Simple ex2;
    ex2 = ex1;
    print(ex2);
    std::cout << ex1 << std::endl;
    return 0;
}