/*
########################

    A jump and run game using SFML C++ library.
    Author: Marc-Antoine Lacroix

    All images and sprite maps: opengameart.org 

########################
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "object.h"
#include "enemy.h"
#include "bullet.h"
#include "health.h"
 
void load_texture(sf::Texture* some_texture,std::string textureFile);
void resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height);
void enemy_detection(Enemy* alien, Player &main_player, Health &healthbar, int &healthTimer, int &healthrefresh, sf::RenderWindow &window);

int main() {
    
    // timers
    float deltaTime {0.0f};
    int shootrefresh {100};
    int shootTimer {0};
    int healthrefresh {300};
    int healthTimer {0};
    int damageTimer {100};
    sf::Clock clock;

    // initialising game window & view
    float SCREEN_WIDTH {800.0};
    float SCREEN_HEIGHT {800.0};
    static const float VIEW_HEIGHT = SCREEN_HEIGHT;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Mr Harry",sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH));
    sf::View HUD(sf::Vector2f(0.0f,0.0f),sf::Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH));

    // main sprite & player
    std::string textureFile {"assets/hero.png"};
    sf::Texture playerTexture;
    load_texture(&playerTexture,textureFile);
    Player main_player(&playerTexture,200.0f,0.2f,200.0f,{8,5},shootrefresh);
    
    // enemy
    std::string alienFile {"assets/alien.png"};
    sf::Texture alienTexture;
    load_texture(&alienTexture,alienFile);
    Enemy* alien = new Enemy(&alienTexture,{100.0f,150.0f},{800.0f,100.0f},true,20,{3,2},0.2f);
    Enemy* alien2 = new Enemy(&alienTexture,{140.0f,200.0f},{2000.0f,60.0f},true,20,{3,2},0.2f);
    Enemy* alien3 = new Enemy(&alienTexture,{250.0f,400.0f},{3000.0f,-100.0f},true,20,{3,2},0.2f);
    Enemy* nu = nullptr;

    // hud elements
    std::string healthFile {"assets/health.png"};
    sf::Texture healthbarTexture;
    load_texture(&healthbarTexture,healthFile);
    Health healthbar(&healthbarTexture,{1,4});

    // game over
    std::string goFile {"assets/gameover.png"};
    sf::Texture goTexture;
    load_texture(&goTexture,goFile);
    sf::RectangleShape go;
    go.setTexture(&goTexture);
    go.setFillColor(sf::Color(40,0,0,160));
    go.setSize(sf::Vector2f{500.0f,500.0f});
    go.setPosition(sf::Vector2f{-250.0f,-250.0f});


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
    load_texture(&floor_texture,floorFile);
    Object floor(&floor_texture,{5000.0f,100.0f},{100.0f,250.0f},true);
    Object floor2(&floor_texture,{90.0f,90.0f},{350.0f,160.0f},true);
    Object floor3(&floor_texture,{90.0f,140.0f},{440.0f,110.0f},true);
    Object floor4(&floor_texture,{90.0f,90.0f},{1150.0f,160.0f},true);
    Object floor5(&floor_texture,{90.0f,120.0f},{1240.0f,130.0f},true);
    
    // platforms
    std::string platFile {"assets/bricks.png"};
    sf::Texture platTexture;
    platTexture.setRepeated(true);
    platTexture.isRepeated();
    load_texture(&platTexture,platFile);
    Object platform(&platTexture,{90.0f,90.0f},{650.0f,50.0f},true);
    Object platform2(&platTexture,{180.0f,90.0f},{1450.0f,50.0f},true);
    platform.GetRect().setTextureRect({0,0,45,45});
    platform2.GetRect().setTextureRect({0,0,90,90});

    //house
    std::string houseFile {"assets/house1.png"};
    sf::Texture house_texture;
    load_texture(&house_texture,houseFile);
    Object house(&house_texture,{200.0f,200.0f},{3000.0f,55.0f},false);
    Object house2(&house_texture,{200.0f,200.0f},{950.0f,55.0f},false);

    //building
    std::string buildingFile {"assets/building.png"};
    sf::Texture building_texture;
    load_texture(&building_texture,buildingFile);
    Object building(&building_texture,{250.0f,400.0f},{1400.0f,-140.0f},false);
    Object building2(&building_texture,{250.0f,400.0f},{1800.0f,-140.0f},false);
    Object building3(&building_texture,{200.0f,370.0f},{2500.0f,-110.0f},false);
    
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
    objects.push_back(floor5);
    objects.push_back(house);
    objects.push_back(house2);
    objects.push_back(lamp);
    objects.push_back(lamp2);
    objects.push_back(lamp3);
    objects.push_back(building);
    objects.push_back(building2);
    objects.push_back(building3);
    objects.push_back(platform);
    objects.push_back(platform2);

    // game loop
    while (window.isOpen()){
        
        deltaTime = clock.restart().asSeconds();
        
        // fix for window dragging
        if(deltaTime > 1.0f / 20.0f){
            deltaTime = 1.0f / 20.0f;
        }  
        if(shootTimer < shootrefresh){
        // delays the rendering of bullets
            shootTimer++;
        }
        if(healthTimer < healthrefresh){
        // delays the health loss effect from ennemies
            healthTimer++;
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
        
        float cur_pos {main_player.getPosition().x};
        if(cur_pos < 1300.0f && alien->Get_Status()){
            alien->Update(deltaTime);
            main_player.Update(deltaTime,shootTimer,objects,*alien);
        }else if(cur_pos < 2500.0f && alien2->Get_Status()){
            alien2->Update(deltaTime);
            main_player.Update(deltaTime,shootTimer,objects,*alien2);
        }else if(alien3->Get_Status()){
            alien3->Update(deltaTime);
            main_player.Update(deltaTime,shootTimer,objects,*alien3);
        }else{
            main_player.Update(deltaTime,shootTimer,objects);
        }

        if(main_player.GetHealthPoints() > 0){
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
            
            if(cur_pos < 1300.0f && alien->Get_Status()){
                enemy_detection(alien,main_player,healthbar,healthTimer,healthrefresh,window);
            }else if(cur_pos < 2500.0f && alien2->Get_Status()){
                enemy_detection(alien2,main_player,healthbar,healthTimer,healthrefresh,window);
            }else if(alien3->Get_Status()){
                enemy_detection(alien3,main_player,healthbar,healthTimer,healthrefresh,window);
            }
            
            main_player.Draw(window);
            
            window.setView(HUD);
            healthbar.Draw(window);
            window.display();

        }else{
            view.rotate(0.002f);
            window.clear(sf::Color(255,200,200,50));
            window.setView(view);
            window.draw(background);
            for(auto object: objects){
                object.setGameOverColor();
                object.Draw(window);
            }
            main_player.Draw(window);
            window.setView(HUD);
            window.draw(go);
            window.display();
        }
    }

    return 0;
}

void resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height) {
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(view_height * aspectRatio,view_height);
}

void load_texture(sf::Texture* some_texture,std::string textureFile){
// loads a texture file
    if(!some_texture->loadFromFile(textureFile)){
        std::cout << "Couldn't load " << textureFile << std::endl;
    }else{
        std::cout << "File loaded succesfully" << std::endl;
    }
}

void enemy_detection(Enemy* alien, Player &main_player, Health &healthbar, int &healthTimer, int &healthrefresh, sf::RenderWindow &window){
// ennemy collision detection
    if(alien->GetCollider().CheckCollision(main_player.GetCollider()) && healthTimer == healthrefresh){
        healthTimer = 0;
        int dam {1};
        main_player.updateHealthPoints(dam);
        main_player.activateHit();
        healthbar.updateHealth(dam);
    }else if (healthTimer==healthrefresh){
        main_player.deactivateHit();
    }
    alien->Draw(window);
}
        