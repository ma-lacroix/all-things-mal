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
    
    if(!m_background_texture.loadFromFile(resourcePath() + "b_background.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_main_texture.loadFromFile(resourcePath() + "b_playing_area.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_second_texture.loadFromFile(resourcePath() + "b_next.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_third_texture.loadFromFile(resourcePath() + "b_score.png")){
        return EXIT_FAILURE;
    }
    
    sf::Vector2f s_size {SCREEN_WIDTH,SCREEN_HEIGHT};
    this->m_color=c_color;
    this->m_font=c_font;
    
    m_background_bg.setSize(s_size);
    m_background_bg.setTexture(&m_background_texture);
    
    m_main_bg.setSize({s_size.x*0.6f,s_size.y*0.8f});
    m_main_bg.setTexture(&m_main_texture);
    
    m_second_bg.setSize({s_size.x*0.270f,s_size.x*0.275f});
    m_second_bg.setTexture(&m_second_texture);
    
    m_third_bg.setSize({s_size.x*0.270f,s_size.x*0.275f});
    m_third_bg.setTexture(&m_third_texture);
    
    m_score.setString("0");
    m_score.setOrigin(0.5f, 0.5f);
    m_score.setFont(m_font);
    m_score.setCharacterSize(s_size.y*0.03);
    m_score.setFillColor(sf::Color::Black);
    
    m_background_bg.setPosition(0.0f,0.0f);
    m_main_bg.setPosition(s_size.x*0.019, s_size.y*0.19);
    m_second_bg.setPosition(s_size.x*0.7, s_size.y*0.35);
    m_third_bg.setPosition(s_size.x*0.7, s_size.y*0.67);
    m_score.setPosition(s_size.x*0.75, s_size.y*0.73);  
}

sf::Vector2f Background::Get_play_size(){
    return m_main_bg.getSize();
}

sf::Vector2f Background::Get_play_pos(){
    return m_main_bg.getPosition();
}

void Background::updateScore(int lines){
    m_lines+=lines;
    m_score.setString(std::to_string(m_lines));
}

void Background::rotateBox(){
    int randv = rand()%23;
    if(randv%2==0){
        m_second_bg.rotate(0.008);
        m_third_bg.rotate(0.01);
        m_score.rotate(0.01);
        m_third_bg.move(-randv%3/50.0f,randv%4/50.0f);
        m_score.move(-randv%3/50.0f,randv%4/50.0f);
    }
    if(randv%2!=0){
        m_second_bg.rotate(-0.008);
        m_third_bg.rotate(-0.02);
        m_score.rotate(-0.02);
        m_third_bg.move(randv%3/50.0f,-randv%4/50.0f);
        m_score.move(randv%3/50.0f,-randv%4/50.0f);
    }
       
}

void Background::Draw(sf::RenderWindow& window, Piece* p){
    window.draw(m_background_bg);
    window.draw(m_main_bg);
    window.draw(m_second_bg);
    window.draw(m_third_bg);
    window.draw(m_score);
    p->DrawNext(window);
}

void Background::Draw(sf::RenderWindow& window){
    window.draw(m_background_bg);
    window.draw(m_main_bg);
    window.draw(m_second_bg);
    window.draw(m_third_bg);
    window.draw(m_score);
}

Background::~Background(){std::cout << "Background destructor called" << std::endl;}
