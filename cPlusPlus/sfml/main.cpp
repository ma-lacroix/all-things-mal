// Testing SFML library

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"

void resizedView(const sf::RenderWindow&, sf::View&, const float view_height);

int main() {
    
    // initialising game window
    float SCREEN_WIDTH {512.0};
    float SCREEN_HEIGHT {512.0};
    static const float VIEW_HEIGHT = SCREEN_HEIGHT;
    std::string textureFile {"tux_from_linux.png"};

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),
                    "Miniman",sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(SCREEN_HEIGHT,
                                                        SCREEN_WIDTH));
    sf::Texture playerTexture;
    
    if(!playerTexture.loadFromFile(textureFile)){
        std::cout << "Couldn't load " << textureFile << std::endl;
    }

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
                resizedView(window,view,VIEW_HEIGHT);
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
        view.setCenter(player.getPosition());
        window.clear(sf::Color(149,149,149));
        window.setView(view);
        player.Draw(window);
        window.display();
    }

    return 0;
}

void resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height) {
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(view_height * aspectRatio,view_height);
}