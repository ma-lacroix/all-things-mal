// struct that initialises the game, renders the game objects and the loop

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "object.h"
#include "enemy.h"
#include "bullet.h"
#include "health.h"

struct main_app{
    void resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height);
    void load_texture(sf::Texture* some_texture,std::string textureFile);
    void enemy_detection(Enemy* alien, Player &main_player, Health &healthbar, int &healthTimer, int &healthrefresh,
                     sf::RenderWindow &window);
    void game(sf::Music& main_song,sf::RenderWindow& window,sf::View view,sf::View HUD,float VIEW_HEIGHT);  
};

void main_app::resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height) {
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(view_height * aspectRatio,view_height);
}

void main_app::load_texture(sf::Texture* some_texture,std::string textureFile){
// loads a texture file
    if(!some_texture->loadFromFile(textureFile)){
        std::cout << "Couldn't load " << textureFile << std::endl;
    }else{
        std::cout << "File loaded succesfully" << std::endl;
    }
}

void main_app::enemy_detection(Enemy* alien, Player &main_player, Health &healthbar, int &healthTimer, int &healthrefresh,
                     sf::RenderWindow &window){
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

void main_app::game(sf::Music& main_song,sf::RenderWindow& window,sf::View view,sf::View HUD,float VIEW_HEIGHT){

    // timers
    float deltaTime {0.0f};
    int shootrefresh {200};
    int shootTimer {0};
    int healthrefresh {300};
    int healthTimer {0};
    int damageTimer {100};
    int gameStartTimer {0};
    int gameEndTimer {0};
    sf::Clock clock;
    bool game_done {false};

    main_song.setPitch(1.0f);
    main_song.setVolume(70);
    main_song.play();
    
    // sounds
    sf::SoundBuffer buffer1;
    sf::Sound pistol1;
    std::string pistol1File {"assets/pistol1.wav"};
    buffer1.loadFromFile(pistol1File);
    pistol1.setBuffer(buffer1);
    pistol1.setVolume(80);
    
    sf::SoundBuffer buffer2;
    sf::Sound pistol2;
    std::string pistol2File {"assets/pistol2.wav"};
    buffer2.loadFromFile(pistol2File);
    pistol2.setBuffer(buffer2);

    sf::SoundBuffer buffer3;
    sf::Sound jump;
    std::string jumpFile {"assets/jump.flac"};
    buffer3.loadFromFile(jumpFile);
    jump.setBuffer(buffer3);

    sf::SoundBuffer buffer4;
    sf::Sound grunt;
    std::string gruntFile {"assets/ouch.flac"};
    buffer4.loadFromFile(gruntFile);
    grunt.setBuffer(buffer4);

    sf::SoundBuffer buffer5;
    sf::Sound monsterGrunt;
    std::string monsterGruntFile {"assets/monsterHit.wav"};
    buffer5.loadFromFile(monsterGruntFile);
    monsterGrunt.setBuffer(buffer5);
    monsterGrunt.setPitch(0.8f);

    std::vector<sf::Sound> sounds;
    sounds.push_back(pistol1);
    sounds.push_back(pistol2);
    sounds.push_back(jump);
    sounds.push_back(grunt);
    sounds.push_back(monsterGrunt);

    // main sprite & player
    std::string textureFile {"assets/hero.png"};
    sf::Texture playerTexture;
    load_texture(&playerTexture,textureFile);
    Player main_player(&playerTexture,200.0f,0.2f,200.0f,{8,5},shootrefresh,sounds);
    
    // enemy
    std::string alienFile {"assets/alien.png"};
    sf::Texture alienTexture;
    load_texture(&alienTexture,alienFile);
    Enemy* alien = new Enemy(&alienTexture,{100.0f,150.0f},{1000.0f,100.0f},true,10,{3,2},0.2f);
    Enemy* alien2 = new Enemy(&alienTexture,{140.0f,200.0f},{2200.0f,60.0f},true,15,{3,2},0.2f);
    Enemy* alien3 = new Enemy(&alienTexture,{200.0f,290.0f},{3500.0f,-200.0f},true,20,{3,2},0.2f);
    Enemy* nu = nullptr;

    // hud elements
    std::string healthFile {"assets/health.png"};
    sf::Texture healthbarTexture;
    load_texture(&healthbarTexture,healthFile);
    Health healthbar(&healthbarTexture,{1,4});

    // game start & over
    std::string gsFile {"assets/gamestart.png"};
    sf::Texture gsTexture;
    load_texture(&gsTexture,gsFile);
    sf::RectangleShape gs;
    gs.setTexture(&gsTexture);
    gs.setSize(sf::Vector2f{500.0f,100.0f});
    gs.setPosition(sf::Vector2f{-250.0f,-250.0f});

    std::string goFile {"assets/gameover.png"};
    sf::Texture goTexture;
    load_texture(&goTexture,goFile);
    sf::RectangleShape go;
    go.setTexture(&goTexture);
    go.setSize(sf::Vector2f{500.0f,500.0f});
    go.setPosition(sf::Vector2f{-250.0f,-250.0f});

    std::string gdFile {"assets/gamedone.png"};
    sf::Texture gdTexture;
    load_texture(&gdTexture,gdFile);
    sf::RectangleShape gd;
    gd.setTexture(&gdTexture);
    gd.setSize(sf::Vector2f{500.0f,500.0f});
    gd.setPosition(sf::Vector2f{-250.0f,-250.0f});

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
    Object floor(&floor_texture,{2400.0f,100.0f},{100.0f,250.0f},true);
    Object floor2(&floor_texture,{90.0f,90.0f},{550.0f,160.0f},true);
    Object floor3(&floor_texture,{90.0f,140.0f},{640.0f,110.0f},true);
    Object floor4(&floor_texture,{90.0f,90.0f},{1350.0f,160.0f},true);
    Object floor5(&floor_texture,{90.0f,120.0f},{1440.0f,130.0f},true);
    Object floor6(&floor_texture,{1500.0f,100.0f},{2700.0f,250.0f},true);
    Object floor7(&floor_texture,{90.0f,90.0f},{3300.0f,160.0f},true);
    
    // platforms
    std::string platFile {"assets/bricks.png"};
    sf::Texture platTexture;
    platTexture.setRepeated(true);
    platTexture.isRepeated();
    load_texture(&platTexture,platFile);
    Object platform(&platTexture,{90.0f,90.0f},{850.0f,50.0f},true);
    Object platform2(&platTexture,{180.0f,90.0f},{1650.0f,50.0f},true);
    platform.GetRect().setTextureRect({0,0,45,45});
    platform2.GetRect().setTextureRect({0,0,45,45});

    //house
    std::string houseFile {"assets/house1.png"};
    sf::Texture house_texture;
    load_texture(&house_texture,houseFile);
    Object house(&house_texture,{200.0f,200.0f},{4000.0f,55.0f},false);
    Object house2(&house_texture,{200.0f,200.0f},{1150.0f,55.0f},false);

    //building
    std::string buildingFile {"assets/building.png"};
    sf::Texture building_texture;
    load_texture(&building_texture,buildingFile);
    Object building(&building_texture,{250.0f,400.0f},{1600.0f,-140.0f},false);
    Object building2(&building_texture,{250.0f,400.0f},{2000.0f,-140.0f},false);
    Object building3(&building_texture,{200.0f,370.0f},{2700.0f,-110.0f},false);
    
    //lamp
    std::string lampFile {"assets/lamp.png"};
    sf::Texture lamp_texture;
    load_texture(&lamp_texture,lampFile);
    Object lamp(&lamp_texture,{50.0f,100.0f},{900.0f,150.0f},false);
    Object lamp2(&lamp_texture,{50.0f,100.0f},{1800.0f,150.0f},false);
    Object lamp3(&lamp_texture,{50.0f,100.0f},{80.0f,150.0f},false);
    
    std::vector<Object> objects;
    objects.push_back(floor);
    objects.push_back(floor2);
    objects.push_back(floor3);
    objects.push_back(floor4);
    objects.push_back(floor5);
    objects.push_back(floor6);
    objects.push_back(floor7);
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
                if (evnt.key.code == sf::Keyboard::R)                
                        game(main_song,window,view,HUD,VIEW_HEIGHT);
                break;
            default:
                break;
            }
            
        }
        
        float cur_pos {main_player.getPosition().x};
        if(cur_pos < 1500.0f && alien->Get_Status()){
            alien->Update(deltaTime);
            main_player.Update(deltaTime,shootTimer,objects,*alien);
        }else if(cur_pos < 2900.0f && alien2->Get_Status()){
            alien2->Update(deltaTime);
            main_player.Update(deltaTime,shootTimer,objects,*alien2);
        }else if(alien3->Get_Status()){
            alien3->Update(deltaTime);
            main_player.Update(deltaTime,shootTimer,objects,*alien3);
        }else{
            main_player.Update(deltaTime,shootTimer,objects);
        }

        if(main_player.GetHealthPoints() > 0){
            
            view.setRotation(0.0f);

            // shake effect when hit
            if(!main_player.HitStatus()){
                view.setCenter(main_player.getPosition().x+200.0f,main_player.getPosition().y);
            }else{
                view.setCenter(main_player.getPosition().x+200.0f,main_player.getPosition().y+std::rand()%23);
            }

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
            
            if(cur_pos < 1500.0f && alien->Get_Status()){
                enemy_detection(alien,main_player,healthbar,healthTimer,healthrefresh,window);
            }else if(cur_pos < 2700.0f && alien2->Get_Status()){
                enemy_detection(alien2,main_player,healthbar,healthTimer,healthrefresh,window);
            }else if(alien3->Get_Status()){
                enemy_detection(alien3,main_player,healthbar,healthTimer,healthrefresh,window);
            }else{
                game_done = true;
            }
            
            main_player.Draw(window);
            
            
            window.setView(HUD);
            if(gameStartTimer < 2000){
                gameStartTimer++;
                gs.setFillColor(sf::Color(255,255,255,250-gameStartTimer/8));
                window.draw(gs);
            }
            if(game_done){
                if(gameEndTimer < 2000){
                    gameEndTimer++;
                }
                if(gameEndTimer==2000){
                    main_song.stop();
                    window.close();
                }
                main_song.setPitch(1.2f);
                main_song.setVolume(100-gameEndTimer/20);
                window.setView(HUD);
                gd.setFillColor(sf::Color(40,0,0,gameEndTimer/8));
                window.draw(gd);
            }

            healthbar.Draw(window);
            window.display();

        }else{
            if(gameEndTimer < 2000){
                gameEndTimer++;
            }
            main_song.setPitch(0.6f);
            view.rotate(0.004f);
            window.clear(sf::Color(255,200,200,50));
            window.setView(view);
            window.draw(background);
            for(auto object: objects){
                object.setGameOverColor();
                object.Draw(window);
            }
            main_player.Draw(window);
            window.setView(HUD);
            go.setFillColor(sf::Color(40,0,0,gameEndTimer/8));
            window.draw(go);
            window.display();
        }
    }
}