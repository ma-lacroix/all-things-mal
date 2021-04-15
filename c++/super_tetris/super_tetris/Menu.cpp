//
//  Menu.cpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 14/04/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Menu.hpp"

Menu::Menu(sf::Font c_font, sf::Vector2f c_screen_size){
    
    this->m_font = c_font;
    m_s_size = 50.0f;
    m_b_size = 80.0f;
    m_selection = 1.0f;
    
    t_introduction = sf::Text("Welcome to \n\nSuperTetris\n\n\nPress Enter!", m_font, m_b_size);
    t_introduction.setFillColor(sf::Color::Black);
    t_introduction.setPosition(c_screen_size.x/10,c_screen_size.y/3);
    
    t_game_over = sf::Text("Game over!", m_font, m_b_size);
    t_game_over.setFillColor(sf::Color::Red);
    t_game_over.setPosition(c_screen_size.x/10,c_screen_size.y/3);
    
    m_others.push_back(t_introduction);
    m_others.push_back(t_game_over);
    
    t_difficulty.setString("SELECT DIFFICULTY:");
    t_easy.setString("1 - Easy peasy");
    t_medium.setString("2 - I can handle it");
    t_hard.setString("3- Dude, seriously");
    t_vhard = sf::Text("4- Ah you #@#@&%##", m_font, m_s_size);
    
    m_difficulty.push_back(t_difficulty);
    m_difficulty.push_back(t_easy);
    m_difficulty.push_back(t_medium);
    m_difficulty.push_back(t_hard);
    m_difficulty.push_back(t_vhard);
    
    float dist {100.0f};
    for(size_t i {0};i<m_difficulty.size();++i){
        m_difficulty.at(i).setFont(m_font);
        m_difficulty.at(i).setCharacterSize(m_s_size);
        m_difficulty.at(i).setFillColor(sf::Color::Black);
        m_difficulty.at(i).setPosition(c_screen_size.x/50,c_screen_size.y/4 + i*dist);
    }
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
        for(auto& msg: m_difficulty){
            window.draw(msg);
        }
    }else{
        window.draw(m_others.at(1));
    }
    
}
