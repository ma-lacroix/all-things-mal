//  SuperTetris
//
//  Created by Marc-Antoine Lacroix on 21/03/2021.
//  Art by Johnny Khalil
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ResourcePath.hpp"
#include "Background.hpp"
#include "Pieces.hpp"
#include "Messages.hpp"
#include "Menu.hpp"

// globals
enum class State {INTRO,DIFFICULTY,PLAYING,GAME_OVER};
const float SCREEN_WIDTH {800.0f};
const float SCREEN_HEIGHT {1500.0f};

void resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height) {
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(view_height * aspectRatio,view_height);
}

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

std::vector<Message*> gen2(sf::Font c_font,int c_size,sf::Vector2f c_pos,float c_speed){
    
    std::vector<std::string> msgs = {"","GOOD!","ALL\n RIGHT!","YEAH\n YEAH\n YEAH!","AWEEE!"};
    std::vector<Message*> c_messages;
    for(int i {0};i<5;++i){
        Message* m = new Message(c_font,c_size,msgs.at(i),c_pos,c_speed);
        c_messages.push_back(m);
    }
    return c_messages;
    
}


int main(){
    
    // time related stuff
    sf::Clock clock;
    sf::Clock clock2;
    float totalTime {0.0f};
    float deltaTime {0.0f};
    float difficulty {1.5f};
    
    sf::Vector2f nextMove {0.0f,0.0f};
    int piece_counter {0};
    int c_index {0};
    
    // Create the main window
    sf::Vector2f screen_size {SCREEN_WIDTH,SCREEN_HEIGHT};
    sf::RenderWindow window(sf::VideoMode(screen_size.x,screen_size.y),"SuperTetris!",sf::Style::Titlebar | sf::Style::Resize);
    sf::View view(screen_size/2.0f,screen_size);
    
    State state = State::INTRO; // for debugging - must be set at INTRO when testing full game
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "Excludedi.ttf")) {
        return EXIT_FAILURE;
    }
    
    Background background(SCREEN_WIDTH,SCREEN_HEIGHT,sf::Color::Red,font);
    std::vector<Piece*> pieces = gen(background.Get_play_size(),background.Get_play_pos(),30);
    std::vector<Message*> messages = gen2(font,300,{SCREEN_WIDTH,SCREEN_HEIGHT/3},10.0f);
    Field* field = new Field();
    Menu* menu = new Menu(font,screen_size);
    
    // Start the game loop
    while (window.isOpen())
    {
        
        totalTime = clock.getElapsedTime().asSeconds();
        deltaTime = clock2.restart().asSeconds();
        
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
            
            if(event.type == sf::Event::Resized){
                resizedView(window,view,SCREEN_HEIGHT);
                printf("New window width: %i New window height: %i\n", event.size.width, event.size.height);
            }
            
            // Start game
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && state == State::INTRO){
                state = State::DIFFICULTY;
            }
            
            if(state == State::DIFFICULTY && event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Num1){
                    difficulty = 1.5f;
                    state = State::PLAYING;
                }else if(event.key.code == sf::Keyboard::Num2){
                    difficulty = 1.0f;
                    state = State::PLAYING;
                }else if(event.key.code == sf::Keyboard::Num3){
                    difficulty = 0.5f;
                    state = State::PLAYING;
                }else if(event.key.code == sf::Keyboard::Num4){
                    difficulty = 0.1f;
                    state = State::PLAYING;
                }
            }
            
            // Move pieces
            if(state == State::PLAYING && event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Left){
                    nextMove = {-1.0f,0.0f};
                }
                if(event.key.code == sf::Keyboard::Right){
                    nextMove = {1.0f,0.0f};
                }
                if(event.key.code == sf::Keyboard::Down){
                    nextMove = {0.0f,1.0f};
                }
                if(event.key.code == sf::Keyboard::Space){
                    nextMove = {99.0f,0.0f};
                }
            }
        }
        
        if(piece_counter==5){
            difficulty-=0.15f; // increase difficulty every 10 pieces
            piece_counter = 0;
        }
        
        if(totalTime>=difficulty && state == State::PLAYING){
            nextMove = {0.0f,1.0f};
            totalTime = clock.restart().asSeconds();
        }
        
        if(field->m_status == Field::Status::RUN && (nextMove.x!=0.0f || nextMove.y!=0.0f)){
            if(nextMove.x!=99.0f){
                pieces.at(c_index)->Move(nextMove, field);
            }else{
                pieces.at(c_index)->Rotate();
            }
            nextMove = {0.0f,0.0f};
            totalTime = clock.restart().asSeconds();
        }
        
        if(field->m_status == Field::Status::UPDATE){
            background.updateScore(field->GetComplSize());
            field->DropLines(background.Get_play_size().x/8, deltaTime,messages);
        }
        
        // Clear screen
        window.clear(sf::Color(200,200,230));
        window.setView(view);
        
        if(state==State::INTRO){
            menu->Draw(window,0);
        }else if(state==State::DIFFICULTY){
            menu->Draw(window,1);
        }else if(state==State::PLAYING){
            if(c_index+1 <= pieces.size()-1){
                background.Draw(window,pieces.at(c_index+1));
                field->Draw(window,messages);
                pieces.at(c_index)->Draw(window);
            }else{
                state = State::GAME_OVER;
            }
        }else{
            menu->Draw(window,2);
        }
        // Update the window
        window.display();
        
        // Switch to next piece
        if(!pieces.at(c_index)->Check_status() && c_index < pieces.size()-1 && field->m_status == Field::Status::RUN){
            ++c_index;
            pieces.at(c_index)->Activate_Piece();
            ++piece_counter;
        }
    }

    return EXIT_SUCCESS;
}
