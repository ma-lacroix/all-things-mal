//  SuperTetris
//
//  Created by Marc-Antoine Lacroix on 21/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ResourcePath.hpp"
#include "Background.hpp"
#include "Pieces.hpp"

enum class State {INTRO,PLAYING,GAME_OVER};
const float SCREEN_WIDTH {800.0f};
const float SCREEN_HEIGHT {1500.0f};

int main()
{
    // Create the main window
    sf::Vector2f screen_size {SCREEN_WIDTH,SCREEN_HEIGHT};
    sf::RenderWindow window(sf::VideoMode(screen_size.x,screen_size.y),"SuperTetris!",sf::Style::Titlebar | sf::Style::Resize);
    
    State state = State::PLAYING; // for debugging - must be set at INTRO when testing full game
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    // Load a sprite to display
//    sf::Texture game_background;
//    if (!game_background.loadFromFile(resourcePath() + "board.png")) {
//        return EXIT_FAILURE;
//    }
//    sf::Sprite sprite(game_background);
//    sprite.setPosition(screen_size.x/5,screen_size.y/5);
    
    
    Background background(SCREEN_WIDTH,SCREEN_HEIGHT,sf::Color::Red,font);
    Piece line(background.Get_play_size(),background.Get_play_pos(),{{0.0f,1.0f},{1.0f,1.0f},{2.0f,1.0f},{3.0f,1.0f}},sf::Color::Blue);
    
    sf::Text introduction("Welcome to SuperTetris", font, 50);
    introduction.setFillColor(sf::Color::Red);
    introduction.setPosition(screen_size.x/5,screen_size.y/2);
    std::vector<sf::Text> messages;
    messages.push_back(introduction);

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
            
            // Start game
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && state == State::INTRO){
                state = State::PLAYING;
            }
            
            // Move pieces
            if(state == State::PLAYING && event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Left){
                    line.Move({-1.0f,0.0f});
                }
                if(event.key.code == sf::Keyboard::Right){
                    line.Move({1.0f,0.0f});
                }
                if(event.key.code == sf::Keyboard::Down){
                    line.Move({0.0f,1.0f});
                }
                // to remove from final game - for debugging purposes only!
                if(event.key.code == sf::Keyboard::Up){
                    line.Move({0.0f,-1.0f});
                }
            }
        }
        
        // Clear screen
        window.clear(sf::Color(229,250,255));
        
        if(state==State::INTRO){
            window.draw(messages.at(0));
        }else if(state==State::PLAYING){
            background.Draw(window);
            line.Draw(window);
        }
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

