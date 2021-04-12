//
//  Messages.cpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 09/04/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Messages.hpp"

Message::Message(sf::Font c_font,int c_size,std::string c_message,sf::Vector2f c_position,float c_speed){

    this->m_font = c_font;
    this->m_font_size = c_size;
    this->m_message = c_message;
    this->m_position = c_position;
    this->m_speed = c_speed;
    
    m_text.setFont(m_font);
    m_text.setString(m_message);
    m_text.setCharacterSize(m_font_size);
    m_text.setPosition(m_position);
    m_text.setFillColor(sf::Color(0,0,0,200));

}

Message::~Message(){
    std::cout << "Message destructor called" << std::endl;
}

void Message::Move(float deltaTime){
    if(m_text.getPosition().x>-3000.0f){
        m_text.move({-deltaTime*m_speed*100.0f,0.0f});
    }
}

void Message::Reset(){
    m_text.setPosition(m_position);
}

void Message::Draw(sf::RenderWindow& window){
    window.draw(m_text);
}

