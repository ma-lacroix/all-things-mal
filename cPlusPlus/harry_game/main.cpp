/*

This code is heavily inspired by an SFML tutorial available on Youtube: https://www.youtube.com/c/HilzeVonck
Credit goes to https://hilzevonck.com/

This code is for the purposes of learning the SFML c++ library. There will be lots of comments and notes!

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

int main() {
    
    // initialising game window
    float SCREEN_WIDTH {512.0};
    float SCREEN_HEIGHT {512.0};

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Robot game",sf::Style::Close | sf::Style::Resize);
    std::string textureFile {"hero.png"};
    sf::Texture playerTexture;

    if(!playerTexture.loadFromFile(textureFile)){
        std::cout << "Couldn't load " << textureFile << std::endl;
    }
    sf::RectangleShape player(sf::Vector2f(100.0f,100.0f));
    player.setPosition(206.0f,206.0f);
    player.setTexture(&playerTexture);

    sf::Vector2u textureSize = playerTexture.getSize();
    textureSize.x /= 8;
    textureSize.y /= 5;

    player.setTextureRect(sf::IntRect(0,0,textureSize.x,textureSize.y));
    
    // The deltatime keeps track of each frame
    float deltaTime = 0.0f;
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
                    printf("Key entered: %c\n",evnt.text.unicode);
                }
                break;
            default:
                break;
            }
            
        }

        window.clear(sf::Color(110,110,100));
        window.draw(player);
        window.display();
    }

    return 0;
}
