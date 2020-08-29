/*
########################

    A jump and run game using SFML C++ library.
    Author: Marc-Antoine Lacroix

    WIP

########################
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "object.h"

void load_texture(sf::Texture* some_texture,std::string textureFile){
// loads a texture file
    if(!some_texture->loadFromFile(textureFile)){
        std::cout << "Couldn't load " << textureFile << std::endl;
    }else{
        std::cout << "File loaded succesfully" << std::endl;
    }
}

void resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height) {
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(view_height * aspectRatio,view_height);
}

int main() {
    
    // initialising game window & view
    float SCREEN_WIDTH {800.0};
    float SCREEN_HEIGHT {800.0};
    static const float VIEW_HEIGHT = SCREEN_HEIGHT;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Mr Harry",sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH));

    // background
    std::string backgroundFile {"sunset.png"};
    sf::Texture backgroundTexture;
    load_texture(&backgroundTexture,backgroundFile);
    sf::Sprite background(backgroundTexture);
    background.setPosition(-500.0f,-500.f);
    background.setColor(sf::Color(255, 255, 255, 110));

    // floor 
    std::string floorFile {"floor.png"};
    sf::Texture floor_texture;
    floor_texture.setRepeated(true);
    floor_texture.isRepeated();
    load_texture(&floor_texture,floorFile);
    Object floor(&floor_texture,{1000.0f,80.0f},{0.0f,445.0f});

    // main sprite
    std::string textureFile {"hero.png"};
    sf::Texture playerTexture;
    load_texture(&playerTexture,textureFile);
    Player main_player(&playerTexture,200.0f,0.2f,200.0f,{8,5});

    // trash cans
    std::vector<Object> objects;
    std::string trashFile {"trash_can.png"};
    sf::Texture trashTexture;
    load_texture(&trashTexture,trashFile);
    // Object trashCan1(&trashTexture,{40.0f,50.0f},{330.0f,395.0f});
    // Object trashCan2(&trashTexture,{40.0f,50.0f},{900.0f,395.0f});
    // Object trashCan3(&trashTexture,{40.0f,50.0f},{1300.0f,395.0f});
    
    // load game objects to vector
    // objects.push_back(trashCan1);
    // objects.push_back(trashCan2);
    // objects.push_back(trashCan3);
    objects.push_back(floor);

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
                resizedView(window,view,VIEW_HEIGHT);
                printf("New window width: %i New window height: %i\n", evnt.size.width, evnt.size.height);
                break;
            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Escape)
                        window.close();
                break;
            default:
                break;
            }
            
        }
        main_player.Update(deltaTime);
        view.setCenter(main_player.getPosition().x+300.0f,main_player.getPosition().y);
        window.clear(sf::Color(110,110,100));
        window.setView(view);
        window.draw(background);
        
        
        // collision detection
        sf::Vector2f direction;
        for(auto object: objects){
            if (object.GetCollider().CheckCollision(main_player.GetCollider(),direction,1.0f)){
                main_player.OnCollision(direction);
            }
        }
        for(auto object: objects){
            object.Draw(window);
        }
        main_player.Draw(window);
        window.display();
        
    }

    return 0;
}
