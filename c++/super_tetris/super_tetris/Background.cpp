//
//  Background.cpp - handles the backgrounds
//  Super_tetris
//
//  Created by Marc-Antoine Lacroix on 23/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Background.hpp"
#include <iostream>

Background::Background(float SCREEN_WIDTH, float SCREEN_HEIGHT,sf::Color c_color, sf::Font c_font){
    
    std::cout << "Background constructor called" << std::endl;
    
    sf::Vector2f s_size {SCREEN_WIDTH,SCREEN_HEIGHT};
    this->m_color=c_color;
    this->m_font=c_font;
    
    m_main_bg.setSize({s_size.x*0.6f,s_size.y*0.8f});
    m_main_bg.setOutlineColor(m_color);
    m_main_bg.setOutlineThickness(3.0f);
    
    m_second_bg.setSize({s_size.x*0.275f,s_size.x*0.275f});
    m_second_bg.setOutlineColor(m_color);
    m_second_bg.setOutlineThickness(3.0f);
    
    m_third_bg.setSize({s_size.x*0.275f,s_size.x*0.275f});
    m_third_bg.setOutlineColor(m_color);
    m_third_bg.setOutlineThickness(3.0f);
    
    m_msg_next.setString("Next:");
    m_msg_next.setFont(m_font);
    m_msg_next.setCharacterSize(s_size.y*0.03);
    m_msg_next.setFillColor(sf::Color::Blue);
    
    m_msg_score.setString("Score:");
    m_msg_score.setFont(m_font);
    m_msg_score.setCharacterSize(s_size.y*0.03);
    m_msg_score.setFillColor(sf::Color::Blue);
    
    m_main_bg.setPosition(s_size.x*0.05, s_size.y*0.1);
    m_second_bg.setPosition(s_size.x*0.7, s_size.y*0.15);
    m_third_bg.setPosition(s_size.x*0.7, s_size.y*0.35);
    m_msg_next.setPosition(s_size.x*0.7, s_size.y*0.1);
    m_msg_score.setPosition(s_size.x*0.7, s_size.y*0.30);
    
}

sf::Vector2f Background::Get_play_size(){
    return m_main_bg.getSize();
}

sf::Vector2f Background::Get_play_pos(){
    return m_main_bg.getPosition();
}

void Background::Draw(sf::RenderWindow& window, Piece* p){
    window.draw(m_main_bg);
    window.draw(m_second_bg);
    window.draw(m_third_bg);
    window.draw(m_msg_next);
    window.draw(m_msg_score);
    p->DrawNext(window);
}

void Background::Draw(sf::RenderWindow& window){
    window.draw(m_main_bg);
    window.draw(m_second_bg);
    window.draw(m_third_bg);
    window.draw(m_msg_next);
    window.draw(m_msg_score);
}

Background::~Background(){std::cout << "Background destructor called" << std::endl;}
