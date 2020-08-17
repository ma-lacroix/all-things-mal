/*############

    A jump and run game using SFML C++ library.
    Author: Marc-Antoine Lacroix

    massive WIP!!!!

############*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
// #include "animation.h"
#include "player.h"

void load_texture(sf::Texture* some_texture,std::string textureFile){
// loads a texture file
    if(!some_texture->loadFromFile(textureFile)){
        std::cout << "Couldn't load " << textureFile << std::endl;
    }else{
        std::cout << "File loaded succesfully" << std::endl;
    }
}

int main() {
    
    // initialising game window
    float SCREEN_WIDTH {512.0};
    float SCREEN_HEIGHT {512.0};
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Mr Harry",sf::Style::Close | sf::Style::Resize);
    
    // main sprite
    std::string textureFile {"hero.png"};
    sf::Texture playerTexture;
    load_texture(&playerTexture,textureFile);
    Player main_player(&playerTexture,0.3f,0.3f,{8,5});
    float deltaTime {0.0f};
    sf::Clock clock;

    // game loop
    while (window.isOpen()){
        
        deltaTime = clock.restart().asSeconds();
        
        // fix for window dragging
        if(deltaTime > 1.0f / 20.0f){
            deltaTime = 1.0f / 20.0f;
        }

        // this part handles events related to the actual game window like closing or resizing. 
        sf::Event evnt;
        while(window.pollEvent(evnt)){
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                printf("New window width: %i New window height: %i\n", evnt.size.width, evnt.size.height);
                break;
            case sf::Event::TextEntered:
                if (evnt.text.unicode < 128){
                    // printf("Key entered: %c\n",evnt.text.unicode);
                }
                break;
            default:
                break;
            }
            
        }
        window.clear(sf::Color(110,110,100));
        main_player.Update(deltaTime);
        main_player.Draw(window);
        window.display();
    }

    return 0;
}
