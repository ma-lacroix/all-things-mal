// struct that initialises the game, renders the game objects and the loop

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "branch.h"
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
    sf::Clock clock;
    sf::Vector2i mouseClickPos;

    Branch rect1({200.0f,50.0f},{100.0f,250.0f});
    Branch rect2({200.0f,50.0f},{400.0f,400.0f});
    Player player({100.0f,100.0f},{300.0f,700.0f});
    std::vector<Branch> rects;
    rects.push_back(rect1);
    rects.push_back(rect2);
    

    // game loop
    while (window.isOpen()){

        deltaTime = clock.restart().asSeconds();
        view.setCenter({0.0f,0.0f});
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
            case sf::Event::MouseButtonPressed:
                mouseClickPos = {evnt.mouseButton.x,evnt.mouseButton.y};
            case sf::Event::MouseButtonReleased:
            default:
                break;
            }
        
        window.clear(sf::Color(30,100,200));
        window.setView(view);
        player.State('S',mouseClickPos,deltaTime);
        
        // handle objects
        for (auto rect: rects){
            if(rect.updateColor(mouseClickPos)){
                player.State('M',mouseClickPos,deltaTime);
            }
            rect.Draw(window);
        }
        player.Draw(window);
        window.display();
        }
    }
}