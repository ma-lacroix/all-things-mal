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

class Background {
private:
    sf::RectangleShape m_main_bg;
    sf::RectangleShape m_second_bg;
    sf::RectangleShape m_third_bg;
    sf::Color m_color;
    sf::Font m_font;
    sf::Text m_msg_next;
    sf::Text m_msg_score;
public:
    Background(float, float,sf::Color,sf::Font);
    ~Background();
    sf::Vector2f Get_play_size();
    sf::Vector2f Get_play_pos();
    void Draw(sf::RenderWindow&);
};

#endif /* Background_hpp */
