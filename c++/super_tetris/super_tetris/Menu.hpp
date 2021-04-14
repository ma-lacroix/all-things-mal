//
//  Menu.hpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 14/04/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Menu {
private:
    std::vector<sf::Text> m_others;
    std::vector<sf::Text> m_difficulty;
    std::size_t m_selection;
    sf::Text t_introduction;
    sf::Text t_game_over;
    sf::Text t_difficulty;
    sf::Text t_easy;
    sf::Text t_medium;
    sf::Text t_hard;
    sf::Text t_vhard;
    
public:
    Menu(sf::Font,sf::Vector2f);
    ~Menu();
    void Move_selector(float);
    void Update_menu_selection();
    void Update_difficulty(float);
    void Draw(sf::RenderWindow&, int);

public:
    float Get_difficulty();
    float m_level;
};

#endif /* Menu_hpp */
