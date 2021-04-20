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
    m_vs_size = 30.0f;
    m_s_size = 50.0f;
    m_b_size = 65.0f;
    m_selection = 1.0f;
    
    t_pause = sf::Text("Pause\n\nSpacebar to restart", m_font, m_s_size);
    t_pause.setFillColor(sf::Color::Red);
    t_pause.setPosition(c_screen_size.x*0.01,c_screen_size.y*0.5);
    
    t_game_over = sf::Text("Game over!", m_font, m_b_size);
    t_game_over.setFillColor(sf::Color::Red);
    t_game_over.setPosition(c_screen_size.x*0.2,c_screen_size.y*0.4);
    
    t_credits = sf::Text("Game development:\nMarc-Antoine Lacroix\n\nArt conception:\nJohnny Khalil", m_font, m_vs_size);
    t_credits.setFillColor(sf::Color::Red);
    t_credits.setPosition(c_screen_size.x*0.05,c_screen_size.y*0.8);
    
    m_others.push_back(t_game_over);
    m_others.push_back(t_credits);
    m_others.push_back(t_pause);
    
    t_difficulty.setString("SELECT DIFFICULTY AND\nPress enter:");
    t_easy.setString("1 - Easy peasy");
    t_medium.setString("2 - I can handle it");
    t_hard.setString("3- Dude, seriously");
    t_vhard.setString("4- Ah you #@#@#@#@");
    t_instructions.setString("Arrows: move pieces\nSpacebar: rotate\nP: pause game\nR: restart");
    
    m_difficulty.push_back(t_difficulty);
    m_difficulty.push_back(t_easy);
    m_difficulty.push_back(t_medium);
    m_difficulty.push_back(t_hard);
    m_difficulty.push_back(t_vhard);
    m_difficulty.push_back(t_instructions);
    
    float dist {100.0f};
    for(size_t i {0};i<m_difficulty.size();++i){
        m_difficulty.at(i).setOrigin(0.0f, m_s_size/2.0f);
        m_difficulty.at(i).setFont(m_font);
        if(i==0){
            m_difficulty.at(i).setCharacterSize(m_s_size);
            m_difficulty.at(i).setFillColor(sf::Color::Black);
            m_difficulty.at(i).setPosition(c_screen_size.x*0.05f,c_screen_size.y*0.3f);
        }else if(i==5){
            m_difficulty.at(i).setCharacterSize(m_vs_size);
            m_difficulty.at(i).setFillColor(sf::Color::Blue);
            m_difficulty.at(i).setPosition(c_screen_size.x*0.05f,c_screen_size.y*0.8f);
        }else{
            m_difficulty.at(i).setCharacterSize(m_s_size);
            m_difficulty.at(i).setFillColor(sf::Color::Black);
            m_difficulty.at(i).setPosition(c_screen_size.x/20.0f,c_screen_size.y*0.4f + i*dist);
        }
    }
    Update_menu_selection();
    
    // sounds
    n1.loadFromFile(resourcePath() + "n_start.wav");
    n_start.setBuffer(n1);
    n_start.setVolume(80);
    
    n2.loadFromFile(resourcePath() + "n_switch.wav");
    n_switch.setBuffer(n2);
    n_switch.setVolume(80);
    
    n3.loadFromFile(resourcePath() + "n_enter.wav");
    n_enter.setBuffer(n3);
    n_enter.setVolume(80);
    
}

Menu::~Menu(){

    std::cout << "menu destructor called" << std::endl;

}


void Menu::Move_selector(float c_move){

        if(m_selection+c_move>=1.0f && m_selection+c_move<=4.0f){
        m_selection+=c_move;
        n_switch.play();
        }
    Update_menu_selection();
}

void Menu::Move_options(float c_totalTime){
    
//    m_difficulty.at(0).move(-sinf(c_totalTime*3.1416)/200.0f,cosf(c_totalTime*3.1416)/200.0f);
    for(size_t i {0};i<m_difficulty.size();++i){
        if(i==m_selection){
            m_difficulty.at(i).move(-sinf(c_totalTime*3.1416)/200.0f,0.0f);
        }
    }
}

void Menu::Update_menu_selection(){
    
    for(size_t i {0};i<m_difficulty.size()-1;++i){
        if(i!=m_selection){
            m_difficulty.at(i).setCharacterSize(m_s_size);
            m_difficulty.at(i).setOutlineThickness(0.0f);
        }else{
            m_difficulty.at(i).setCharacterSize(m_b_size);
            m_difficulty.at(i).setOutlineColor(sf::Color::Red);
            m_difficulty.at(i).setOutlineThickness(3.0f);
        }
    }
}

float Menu::Get_difficulty(){
    if(m_selection==1.0f){
        m_level = 1.5f;
    }else if(m_selection==2.0f){
        m_level = 1.0f;
    }else if(m_selection==3.0f){
        m_level = 0.5f;
    }else if(m_selection==4.0f){
        m_level = 0.1f;
    }
    
    n_enter.play();
    
    return m_level;

}

void Menu::Play_d_menu(){
    n_start.play();
}

void Menu::Draw(sf::RenderWindow& window, int c_index){
    
    if(c_index==1){
        for(auto& msg: m_difficulty){
            window.draw(msg);
        }
    }else if(c_index==2){
        window.draw(m_others.at(0));
        window.draw(m_others.at(1));
    }else{
        window.draw(m_others.at(2));
    }
    
}
