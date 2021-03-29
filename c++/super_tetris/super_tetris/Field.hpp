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
#include <list>

class Field {
private:
    std::vector<sf::RectangleShape> m_field;
    std::map<float,int> m_inventory;
    
public:
    Field();
    ~Field();
    void DropLines(float,float);
    void EraseLines(float, float);
    void CheckLines(sf::RectangleShape,float);
    void Add_field(sf::RectangleShape,float);
    int Collision(sf::RectangleShape,sf::Vector2f,sf::Vector2f);
    void Draw(sf::RenderWindow&);
};

#endif /* Field_hpp */
