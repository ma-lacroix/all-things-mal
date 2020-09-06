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
#include "bullet.h"

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

    // main sprite & player
    std::string textureFile {"assets/hero.png"};
    sf::Texture playerTexture;
    load_texture(&playerTexture,textureFile);
    Player main_player(&playerTexture,200.0f,0.2f,200.0f,{8,5});
    
    // background
    std::string backgroundFile {"assets/sunset.png"};
    sf::Texture backgroundTexture;
    load_texture(&backgroundTexture,backgroundFile);
    sf::Sprite background(backgroundTexture);
    background.setPosition(-500.0f,-700.f);
    background.setColor(sf::Color(255, 255, 255, 110));

    // floors 
    std::string floorFile {"assets/floor.png"};
    sf::Texture floor_texture;
    floor_texture.setRepeated(true);
    floor_texture.isRepeated();
    load_texture(&floor_texture,floorFile);
    Object floor(&floor_texture,{3000.0f,100.0f},{100.0f,250.0f},true);
    Object floor2(&floor_texture,{90.0f,90.0f},{400.0f,160.0f},true);
    Object floor3(&floor_texture,{90.0f,90.0f},{1150.0f,160.0f},true);
    Object floor4(&floor_texture,{90.0f,120.0f},{1240.0f,130.0f},true);

    //house
    std::string houseFile {"assets/house1.png"};
    sf::Texture house_texture;
    load_texture(&house_texture,houseFile);
    Object house(&house_texture,{200.0f,200.0f},{650.0f,55.0f},false);
    Object house2(&house_texture,{200.0f,200.0f},{950.0f,55.0f},false);

    //building
    std::string buildingFile {"assets/building.png"};
    sf::Texture building_texture;
    load_texture(&building_texture,buildingFile);
    Object building(&building_texture,{250.0f,400.0f},{1400.0f,-140.0f},false);
    Object building2(&building_texture,{250.0f,400.0f},{1800.0f,-140.0f},false);
    
    //lamp
    std::string lampFile {"assets/lamp.png"};
    sf::Texture lamp_texture;
    load_texture(&lamp_texture,lampFile);
    Object lamp(&lamp_texture,{50.0f,100.0f},{900.0f,150.0f},false);
    Object lamp2(&lamp_texture,{50.0f,100.0f},{1600.0f,150.0f},false);
    Object lamp3(&lamp_texture,{50.0f,100.0f},{80.0f,150.0f},false);
    
    std::vector<Object> objects;
    objects.push_back(floor);
    objects.push_back(floor2);
    objects.push_back(floor3);
    objects.push_back(floor4);
    objects.push_back(house);
    objects.push_back(house2);
    objects.push_back(lamp);
    objects.push_back(lamp2);
    objects.push_back(lamp3);
    objects.push_back(building);
    objects.push_back(building2);

    float deltaTime {0.0f};
    int shootTimer {0};
    sf::Clock clock;

    // game loop
    while (window.isOpen()){
        
        deltaTime = clock.restart().asSeconds();
        
        // fix for window dragging
        if(deltaTime > 1.0f / 20.0f){
            deltaTime = 1.0f / 20.0f;
        }  
        if(shootTimer < 50){
            shootTimer++;
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

        main_player.Update(deltaTime,shootTimer,objects);
        view.setCenter(main_player.getPosition().x+200.0f,main_player.getPosition().y);
        window.clear(sf::Color(110,110,100));
        window.setView(view);
        window.draw(background);
        
        // collision detection
        sf::Vector2f direction;
        for(auto object: objects){
            if(object.Clipping()){
                if (object.GetCollider().CheckCollision(main_player.GetCollider(),direction,1.0f)){
                main_player.OnCollision(direction);
                }
            }
        }

        // drawing game objects
        for(auto object: objects){
            object.Draw(window);
        }
        for(auto bullet: main_player.getBullets()){
            bullet->Draw(window);
        }
        main_player.Draw(window);
        window.display();
        
    }

    return 0;
}
