#include <iostream>
#include <list>

int main(){
    
    std::list<int> testing {10,40,40};
    testing.push_front(5);

    std::list<int>::iterator it = testing.begin();
    ++it;
    testing.insert(it,32);

    for(it = testing.begin();it != testing.end();++it){
        std::cout << *it << " ";
    }


    return 0;
}