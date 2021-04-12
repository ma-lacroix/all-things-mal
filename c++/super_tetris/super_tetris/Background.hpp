//
//  Background.hpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 23/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#ifndef Background_hpp
#define Background_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pieces.hpp"

class Background {
private:
    sf::RectangleShape m_background_bg;
    sf::Texture m_background_texture;
    sf::RectangleShape m_main_bg;
    sf::Texture m_main_texture;
    sf::RectangleShape m_second_bg;
    sf::Texture m_second_texture;
    sf::RectangleShape m_third_bg;
    sf::Texture m_third_texture;
    sf::Color m_color;
    sf::Font m_font;
    sf::Text m_msg_next;
    sf::Text m_msg_score;
    sf::Text m_score;
    int m_lines;
    
public:
    Background(float, float,sf::Color,sf::Font);
    ~Background();
    sf::Vector2f Get_play_size();
    sf::Vector2f Get_play_pos();
    void updateScore(int);
    void Draw(sf::RenderWindow&,Piece*);
    void Draw(sf::RenderWindow&);
    
};

#endif /* Background_hpp */
