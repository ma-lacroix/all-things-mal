// game inventory management class

#ifndef _INVENTORY_H_
#define _INVENTORY_H_
#include <iostream>
#include <string>
#include <vector>

class Game {

private:
    std::vector<int> ind;
    std::vector<std::string> name;
    std::vector<std::string> type;
    std::vector<int> year_release;    
    std::vector<int> score;

public:
    Game(); // trouble with initializing variables in the constructor
    void add_new_game(std::vector<int>&,std::vector<std::string>&,std::vector<std::string>&,std::vector<int>&,std::vector<int>&);
    void print_games(std::vector<int>,std::vector<std::string>,std::vector<std::string>,std::vector<int>,std::vector<int>);
};

// Game::Game()

int number_games() {
    int num;
    std::cout << "How many games would you like to add: ";
    std::cin >> num;
    std::cout << "\nWe will add " << num << " games today.\n" << std::endl;
    return num;
}

void Game::add_new_game(std::vector<int> &ind,std::vector<std::string> &name,\
                        std::vector<std::string> &type,std::vector<int> &year_release,\
                        std::vector<int> &score) {
    int n;
    std::string game_name;
    std::string game_type;
    int year;
    int rate;
    n = number_games();
    for (int i = 0;i<n;++i) {
        std::cout << "What is the name of the game? ";
        std::cin >> game_name;
        std::cout << "What year was it released? ";
        std::cin >> year;
        std::cout << "What kind of game is it? ";
        std::cin >> game_type;
        std::cout << "What score would you give your game out of 5? ";
        std::cin >> rate;
        ind.push_back(i+1);
        name.push_back(game_name);
        type.push_back(game_type);
        year_release.push_back(year);
        score.push_back(rate);
    }
}

void Game::print_games(std::vector<int> ind,std::vector<std::string> name,\
                        std::vector<std::string> type,std::vector<int> year_release,\
                        std::vector<int> score){
    
    std::cout << "=========================================================================" << std::endl;
    for (size_t i=0;i<ind.size();++i) {
        std::cout << "Index: " << ind[i] << " | ";
        std::cout << "Name:  " << name[i] << " | ";
        std::cout << "Type:  " << type[i] << " | ";
        std::cout << "Year:  " << year_release[i] << " | ";
        std::cout << "Score: " << score[i] << "/5" << std::endl << std::endl;
    }
    std::cout << "=========================================================================" << std::endl;
}

#endif
