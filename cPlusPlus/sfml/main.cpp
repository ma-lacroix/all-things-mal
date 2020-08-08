// Testing SFML library

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

int main() {
    
    // initialising game window
    int SCREEN_WIDTH {512};
    int SCREEN_HEIGHT {512};
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),
                    "Miniman",sf::Style::Close | sf::Style::Resize);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("tux_from_linux.png");

    Player player(&playerTexture,sf::Vector2u(3,9),0.3f,100.0f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    // game loop
    while (window.isOpen()){

        deltaTime = clock.restart().asSeconds();
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

        player.Update(deltaTime);
        window.clear(sf::Color(149,149,149));
        player.Draw(window);
        window.display();
    }

    return 0;
}