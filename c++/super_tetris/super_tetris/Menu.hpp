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
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"

class Menu {
private:
    std::vector<sf::Text> m_others;
    std::vector<sf::Text> m_difficulty;
    std::size_t m_selection;
    int m_vs_size;
    int m_s_size;
    int m_b_size;
    sf::Font m_font;
    sf::Text t_introduction;
    sf::Text t_begin;
    sf::Text t_pause;
    sf::Text t_game_over;
    sf::Text t_credits;
    sf::Text t_difficulty;
    sf::Text t_easy;
    sf::Text t_medium;
    sf::Text t_hard;
    sf::Text t_vhard;
    sf::Sound n_start;
    sf::SoundBuffer n1;
    sf::Sound n_switch;
    sf::SoundBuffer n2;
    sf::Sound n_enter;
    sf::SoundBuffer n3;
    
public:
    Menu(sf::Font,sf::Vector2f);
    ~Menu();
    float Get_difficulty();
    void Move_selector(float);
    void Move_options(float);
    void Update_menu_selection();
    void Play_d_menu();
    void Draw(sf::RenderWindow&, int);

public:
    float m_level;
};

#endif /* Menu_hpp */
