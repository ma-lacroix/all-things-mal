//
//  Pieces.hpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 23/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#ifndef Pieces_hpp
#define Pieces_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Piece {
private:
    std::vector<sf::Vector2f> m_init;
    std::vector<sf::Vector2f> m_positions;
    std::vector<sf::RectangleShape> m_squares;
    sf::Vector2f m_block_size;
    sf::Vector2f m_play_size;
    sf::Vector2f m_play_pos;
    sf::Color m_color;
    bool m_is_alive;
    
public:
    Piece(sf::Vector2f,sf::Vector2f,std::vector<sf::Vector2f>,sf::Color);
    ~Piece();
    bool Check_boundaries(sf::Vector2f);
    bool Check_bottom();
    void Move(sf::Vector2f);
    void Rotate();
    void Draw(sf::RenderWindow&);
};

#endif /* Pieces_hpp */
