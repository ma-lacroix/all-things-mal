#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <string>

std::map<int,std::string> gen_menu(std::string file){

    std::map<int,std::string> menu;
    std::fstream infile;
    infile.open(file,std::ios::in);
    if(infile.is_open()){
        std::string line;
        int i {1};
        while(infile){
            std::getline(infile,line);
            infile >> std::ws;
            menu[i] = line;
            ++i;
        }
    }
    return menu;
}

void print_menu(std::map<int,std::string> menu){
    for(std::map<int,std::string>::iterator it = menu.begin();it!=menu.end();++it){
        std::cout << it->first << " " << it->second << std::endl;
    }
}

int main(){
    std::cout << std::flush;
    int choice {0};
    std::map<int,std::string> menu = gen_menu("text.txt");
    do {
        print_menu(menu);
        std::cout << "Enter choice (0-9): " << std::endl;
        std::cin >> choice;
        std::cout << "You have selected:" << menu.find(choice)->second << std::endl;
    }while(choice != 9);
    
    return 0;
}