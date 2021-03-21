//
//  game_logic.cpp
//  tic_tac_toe
//
//  Created by Marc-Antoine Lacroix on 21/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ResourcePath.hpp"
#include "game_logic.hpp"

enum class State {INTRO,PLAYING,GAME_OVER};

int main(int, char const**)
{
    // Create the main window
    sf::Vector2f screen_size {800.0,800.0};
    sf::RenderWindow window(sf::VideoMode(screen_size.x,screen_size.y),"TIC TAC TOE",sf::Style::Titlebar | sf::Style::Resize);
    
    State state = State::INTRO;
    
    // Set the Icon
//    sf::Image icon;
//    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
//        return EXIT_FAILURE;
//    }
//    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture game_background;
    if (!game_background.loadFromFile(resourcePath() + "board.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(game_background);
    sprite.setPosition(screen_size.x/5,screen_size.y/5);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text introduction("Welcome to Tic Tac Toe!", font, 50);
    introduction.setFillColor(sf::Color::Red);
    introduction.setPosition(screen_size.x/5,screen_size.y/2);
    sf::Text player1("Player 1 move", font, 50);
    sf::Text player2("Player 2 move", font, 50);
    player1.setFillColor(sf::Color::Blue);
    player2.setFillColor(sf::Color::Blue);
    std::vector<sf::Text> messages;
    messages.push_back(introduction);
    messages.push_back(player1);
    messages.push_back(player2);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && state == State::INTRO){
                state = State::PLAYING;
            }
        }
        
        // Clear screen
        window.clear();
        
        if(state==State::INTRO){
            window.draw(messages.at(0));
        }else if(state==State::PLAYING){
            window.draw(sprite);
            window.draw(messages.at(1));
        }
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
