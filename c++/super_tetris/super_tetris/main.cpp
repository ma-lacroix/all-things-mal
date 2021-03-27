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

// globals
enum class State {INTRO,PLAYING,GAME_OVER};
const float SCREEN_WIDTH {800.0f};
const float SCREEN_HEIGHT {1500.0f};
int c_index {0};


std::vector<Piece*> gen(sf::Vector2f c_play_size, sf::Vector2f c_play_pos, int num_pieces){
    
    std::vector<Piece*> c_pieces;
    for(int i {0};i<num_pieces;++i){
        srand((int)time(0) * i * 2);
        int c_type = (rand() % 5)+1;
        Piece* p = new Piece(c_play_size,c_play_pos,c_type);
        c_pieces.push_back(p);
    }
    c_pieces.at(0)->Activate_Piece();
    return c_pieces;
}


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
    
    Background background(SCREEN_WIDTH,SCREEN_HEIGHT,sf::Color::Red,font);
    std::vector<Piece*> pieces = gen(background.Get_play_size(),background.Get_play_pos(),30);
    Field* field = new Field();
    
    sf::Text t_introduction("Welcome to SuperTetris", font, 50);
    t_introduction.setFillColor(sf::Color::Red);
    t_introduction.setPosition(screen_size.x/5,screen_size.y/2);
    
    sf::Text t_game_over("Game over", font, 50);
    t_game_over.setFillColor(sf::Color::Red);
    t_game_over.setPosition(screen_size.x/2,screen_size.y/2);

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
                    pieces.at(c_index)->Move({-1.0f,0.0f},field);
                }
                if(event.key.code == sf::Keyboard::Right){
                    pieces.at(c_index)->Move({1.0f,0.0f},field);
                }
                if(event.key.code == sf::Keyboard::Down){
                    pieces.at(c_index)->Move({0.0f,1.0f},field);
                }
                if(event.key.code == sf::Keyboard::Space){
                    pieces.at(c_index)->Rotate();
                }
            }
        }
        
        // Clear screen
        window.clear(sf::Color(100,100,120));
        
        if(state==State::INTRO){
            window.draw(t_introduction);
        }else if(state==State::PLAYING){
            if(c_index+1 <= pieces.size()-1){
                background.Draw(window,pieces.at(c_index+1));
                field->Draw(window);
                pieces.at(c_index)->Draw(window);
            }else{
                state = State::GAME_OVER;
            }
        }else{
            window.draw(t_game_over);
        }
        // Update the window
        window.display();
        
        // Switch to next piece
        if(!pieces.at(c_index)->Check_status() && c_index < pieces.size()-1){
            ++c_index;
            pieces.at(c_index)->Activate_Piece();
        }
    }

    return EXIT_SUCCESS;
}

