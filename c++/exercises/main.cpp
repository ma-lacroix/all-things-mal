#include <iostream>

struct Solution {
    
    int num1 {0};
    int num2 {0};
    Solution(int num_1, int num_2){
        this->num1=num_1;
        this->num2=num_2;
    }
    ~Solution(){}
    
    void printNums(){
        std::cout << num1 << std::endl;
        std::cout << num2 << std::endl;
    }
    int sumNums(){
        return num1+num2;
    }
};

int main(){
    Solution* sol = new Solution(10,20);
    int total = sol->sumNums();
    std::cout << total << std::endl;
    sol->printNums();
    return 0;
}