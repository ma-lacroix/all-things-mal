//
//  Field.hpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 25/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#ifndef Field_hpp
#define Field_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Field {
private:
    std::vector<sf::RectangleShape> m_field;
public:
    Field();
    ~Field();
    void Add_field(sf::RectangleShape);
    void Print();
    int Collision(sf::RectangleShape,sf::Vector2f,sf::Vector2f);
};

#endif /* Field_hpp */
