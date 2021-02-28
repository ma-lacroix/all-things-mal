// example with vector itterator

#include <iostream>
#include <vector>

void exampleA() {
    std::vector<int> nums;
    nums.push_back(2);
    nums.push_back(4);
    nums.push_back(5);
    nums.push_back(9);

    for(std::vector<int>::iterator it = nums.begin();it!=nums.end();++it){
        std::cout << *it << std::endl;
    }
}

void exampleB() {
    std::vector<std::vector<int>> matrix;
    matrix.push_back({1,0,0});
    matrix.push_back({0,1,0});
    matrix.push_back({0,0,1});

    for(size_t i {0};i<matrix.size();++i){
        for(std::vector<int>::iterator it = matrix.at(i).begin();it != matrix.at(i).end();++it){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

}

int main(){

    exampleB();
    std::cout << "Done." << std::endl;

    return 0;
}