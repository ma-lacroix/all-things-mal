//
//  Messages.hpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 09/04/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#ifndef Messages_hpp
#define Messages_hpp
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

class Message{
private:
    sf::Font m_font;
    int m_font_size;
    std::string m_message;
    sf::Vector2f m_position;
    float m_speed;
    sf::Text m_text;
    
public:
    Message(sf::Font,int,std::string,sf::Vector2f,float);
    ~Message();
    void Move(float);
    void Reset();
    void Draw(sf::RenderWindow&);
    
};

#endif /* Messages_hpp */
