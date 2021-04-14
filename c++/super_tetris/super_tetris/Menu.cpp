//
//  Menu.cpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 14/04/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Menu.hpp"

Menu::Menu(sf::Font c_font, sf::Vector2f c_screen_size){
    
    m_selection = 1.0f;
    
    t_introduction = sf::Text("Welcome to \n\nSuperTetris\n\n\nPress Enter!", c_font, 80);
    t_introduction.setFillColor(sf::Color::Black);
    t_introduction.setPosition(c_screen_size.x/10,c_screen_size.y/3);
    
    t_game_over = sf::Text("Game over!", c_font, 80);
    t_game_over.setFillColor(sf::Color::Red);
    t_game_over.setPosition(c_screen_size.x/10,c_screen_size.y/3);
    
    m_others.push_back(t_introduction);
    m_others.push_back(t_game_over);
    
    t_difficulty = sf::Text("SELECT DIFFICULTY:", c_font, 80);
    t_difficulty.setFillColor(sf::Color::Black);
    t_difficulty.setPosition(c_screen_size.x/10,c_screen_size.y/4);
    
    t_easy = sf::Text("1 - Easy peasy", c_font, 80);
    t_easy.setFillColor(sf::Color::Black);
    t_easy.setPosition(c_screen_size.x/10,c_screen_size.y/4 + 25.0f);
    
    t_medium = sf::Text("2 - I can handle it", c_font, 80);
    t_medium.setFillColor(sf::Color::Black);
    t_medium.setPosition(c_screen_size.x/10,c_screen_size.y/4 + 50.0f);
    
    t_hard = sf::Text("3- Dude, seriously", c_font, 80);
    t_hard.setFillColor(sf::Color::Black);
    t_hard.setPosition(c_screen_size.x/10,c_screen_size.y/4 + 75.0f);
    
    t_vhard = sf::Text("4- Ah you #@#@&%##", c_font, 80);
    t_vhard.setFillColor(sf::Color::Black);
    t_vhard.setPosition(c_screen_size.x/10,c_screen_size.y/4 + 100.0f);
    
    m_difficulty.push_back(t_difficulty);
    m_difficulty.push_back(t_easy);
    m_difficulty.push_back(t_medium);
    m_difficulty.push_back(t_hard);
    m_difficulty.push_back(t_vhard);
    
}

Menu::~Menu(){

    std::cout << "menu destructor called" << std::endl;

}


void Menu::Move_selector(float c_move){
    
    if(m_selection-c_move>=1.0f){
        m_selection-=c_move;
    }else if(m_selection+c_move>4.0f){
        m_selection=1.0f;
    }else{
        m_selection+=c_move;
    }
    Update_menu_selection();
}

void Menu::Update_menu_selection(){
    
    for(size_t i {0};i<m_difficulty.size();++i){
        if(i!=m_selection){
            m_difficulty.at(i).setCharacterSize(50);
        }else{
            m_difficulty.at(i).setCharacterSize(80);
        }
    }
    
}

void Menu::Update_difficulty(float val){

    m_level += val;

}

float Menu::Get_difficulty(){
    
    return m_level;

}

void Menu::Draw(sf::RenderWindow& window, int c_index){
    
    if(c_index==0){
        window.draw(m_others.at(0));
    }else if(c_index==1){
        window.draw(m_others.at(1));
    }else{
        window.draw(t_difficulty);
//        for(auto& msg: m_difficulty){
//            window.draw(msg);
//        }
    }
    
}
