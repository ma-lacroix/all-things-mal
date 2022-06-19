#ifndef CC_hpp
#define CC_hpp
#include <string>

class creditCard
{
private:
    std::string cc_number;
    bool status;    
public:
    creditCard(std::string);
    ~creditCard();
    bool checkStatus();
    std::string getCC();
    bool getStatus();
};

#endif // CC_hpp