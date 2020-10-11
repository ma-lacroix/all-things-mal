// struct that initialises the game, renders the game objects and the loop

#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "branch.h"
#include "trunk.h"
#include "player.h"

struct app{
    void game(sf::RenderWindow& window,sf::View view,sf::View HUD,float VIEW_HEIGHT);  
    void resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height);
};

void app::resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height) {
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(view_height * aspectRatio,view_height);
}

void app::game(sf::RenderWindow& window,sf::View view,sf::View HUD,float VIEW_HEIGHT){

    // timers
    float deltaTime {0.0f};
    float Ycoord {0.0f};
    sf::Clock clock;

    // Tree branches
    Branch* rect1 = new Branch({200.0f,50.0f},{100.0f,150.0f});
    Branch* rect2 = new Branch({300.0f,50.0f},{300.0f,300.0f});
    Branch* rect3 = new Branch({200.0f,50.0f},{150.0f,600.0f});
    Branch* rect4 = new Branch({200.0f,50.0f},{250.0f,800.0f});
    Branch* rect5 = new Branch({200.0f,50.0f},{90.0f,1000.0f});
    std::vector<Branch*> rects;
    rects.push_back(rect1);
    rects.push_back(rect2);
    rects.push_back(rect3);
    rects.push_back(rect4);
    rects.push_back(rect5);

    // Tree trunk pieces
    Trunk* trunk1 = new Trunk({100.0f,300.0f},{275.0f,800.0f});
    Trunk* trunk2 = new Trunk({100.0f,300.0f},{285.0f,500.0f});
    Trunk* trunk3 = new Trunk({100.0f,300.0f},{275.0f,200.0f});
    Trunk* trunk4 = new Trunk({100.0f,300.0f},{285.0f,-100.0f});
    std::vector<Trunk*> trunks;
    trunks.push_back(trunk1);
    trunks.push_back(trunk2);
    trunks.push_back(trunk3);
    trunks.push_back(trunk4);

    // main player & its arms
    Player* player_arm = new Player({0.0f,40.0f},{300.0f,1100.0f},900.0f,true);
    Player* main_player = new Player({100.0f,100.0f},{300.0f,1100.0f},100.0f,false);
    std::vector<Player*> players;
    players.push_back(player_arm);
    players.push_back(main_player);

    // game loop
    while (window.isOpen()){

        deltaTime = clock.restart().asSeconds();
        view.setCenter(VIEW_HEIGHT/2,main_player->getPosition().y-100.0f);
        
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
                    game(window,view,HUD,VIEW_HEIGHT);
                break;
            default:
                break;
            }
        }
        
        // handle & draw objects
        window.clear(sf::Color(245,230,230));
        window.setView(view);
        Ycoord = view.getCenter().y;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            for (auto plr: players){
                plr->setMouseClickPos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                plr->Rotate();
                plr->ifClickToRight();
            }
        }
        
        for (auto trunk: trunks){
            trunk->updateYcoord(Ycoord);
            trunk->Draw(window);
        }

        for (auto rect: rects){
            rect->updateYcoord(Ycoord);
            rect->updateColor(rect->Collision(main_player->getClickPos(),main_player->getVelocity().y));
            rect->Draw(window);
        }
        
        
        for (auto plr: players){
            for (auto rect: rects){
                if(rect->Collision(plr->getClickPos(),plr->getVelocity().y)){
                    plr->updateState('M');
                    plr->AdjustArm(players.at(1)->getPosition());
                    plr->State(deltaTime);
                    plr->Draw(window);
                    break;
                }else{
                    plr->updateState('S');
                    plr->AdjustArm(players.at(1)->getPosition());
                    plr->State(deltaTime);
                    plr->Draw(window);
                }
            }
        }
        window.display();
    }
}