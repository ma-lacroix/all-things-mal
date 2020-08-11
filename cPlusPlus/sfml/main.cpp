/*

This is the code from an SFML tutorial available on Youtube: https://www.youtube.com/c/HilzeVonck
All credit goes to https://hilzevonck.com/

This code is for the purposes of learning the SFML c++ library. There will be lots of comments and notes! 

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Platform.h"
#include "Collider.h"

void resizedView(const sf::RenderWindow&, sf::View&, const float view_height);

int main() {
    
    // initialising game window
    float SCREEN_WIDTH {512.0};
    float SCREEN_HEIGHT {512.0};
    static const float VIEW_HEIGHT = SCREEN_HEIGHT; // a variable used to make sure the game window's elements are kept intact

    // The RenderWindow class creates an actual game window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Miniman",sf::Style::Close | sf::Style::Resize);
    // The View basically sets the camera for the gameplay
    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH));
    
    // textures are loaded using the Texture class and its loadfromfile member function
    std::string textureFile {"tux_from_linux.png"};
    sf::Texture playerTexture;
    std::string boxfile {"crate.png"};
    sf::Texture boxTexture;

    if(!playerTexture.loadFromFile(textureFile)){
        std::cout << "Couldn't load " << textureFile << std::endl;
    }
    if(!boxTexture.loadFromFile(boxfile)){
        std::cout << "Couldn't load " << boxfile << std::endl;
    }

    // Player Class constructor is called passing in a texture file as well as movement speed and jump height
    Player player(&playerTexture,sf::Vector2u(3,9),0.3f,200.0f, 200.f);
    
    // These are actual objects which collide with the player instance
    std::vector<Platform> platforms;
    platforms.push_back(Platform(&boxTexture,sf::Vector2f(100.0f,100.0f),sf::Vector2f(500.0f,725.0f)));
    platforms.push_back(Platform(&boxTexture,sf::Vector2f(150.0f,150.0f),sf::Vector2f(100.0f,700.0f)));
    platforms.push_back(Platform(nullptr,sf::Vector2f(10000.0f,50.0f),sf::Vector2f(500.0f,800.0f)));
    
    // Turns the body of the player into a Collider class instance
    Collider playerCollision = player.GetCollider();
    
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

        // this part handles events related to the actual game window
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

        sf::Vector2f direction;

        for(Platform& platform: platforms){
            if (platform.GetCollider().CheckCollision(player.GetCollider(),direction,1.0f)){
                player.OnCollision(direction);
            }
        }
        
        view.setCenter(player.getPosition());
        window.clear(sf::Color(149,149,149));
        window.setView(view);
        player.Draw(window);
        for(Platform& platform: platforms){
            platform.Draw(window);
        }
        window.display();
    }

    return 0;
}

void resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height) {
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(view_height * aspectRatio,view_height);
}