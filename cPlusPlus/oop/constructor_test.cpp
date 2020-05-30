// trying out constructors and copy constructors

#include <iostream>

using namespace std;

class Power {
private:
    int num;

public:
    void print_obj();
    int get_num() {return num;}
    Power();
    Power(const Power &source);
};

Power::Power()
    : num(0) {}

Power::Power(const Power &source)
    : num(source.num) {
        cout << "Calling class constructor copier" << endl;
    }

void Power::print_obj() {
    cout << num << endl;
}

void add_num(Power p) {
    cout << p.get_num()+10 << endl;
}

int main() {
    Power test;
    test.print_obj();
    add_num(test);
    Power test2 (test);
    add_num(test2);
    return 0;
}