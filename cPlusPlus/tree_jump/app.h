// struct that initialises the game, renders the game objects and the loop

#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "branch.h"
#include "notes.h"
#include "trunk.h"
#include "player.h"

struct app{
    void game(sf::RenderWindow& window,sf::View view,sf::View HUD,float VIEW_WIDTH);  
    void resizedView(const sf::RenderWindow& window, sf::View& view, const float VIEW_WIDTH);
    void load_texture(sf::Texture* some_texture,std::string textureFile);
};

void app::resizedView(const sf::RenderWindow& window, sf::View& view, const float VIEW_WIDTH) {
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(VIEW_WIDTH * aspectRatio,VIEW_WIDTH);
}

void app::load_texture(sf::Texture* some_texture,std::string textureFile){
// loads a texture file
    if(!some_texture->loadFromFile(textureFile)){
        std::cout << "Couldn't load " << textureFile << std::endl;
    }else{
        std::cout << "File loaded succesfully" << std::endl;
    }
}

void app::game(sf::RenderWindow& window,sf::View view,sf::View HUD,float VIEW_WIDTH){

    // timers
    float deltaTime {0.0f};
    float totalTime {0.0f};
    float Ycoord {0.0f};
    size_t rectsLen {0};
    int i {1};
    sf::Clock clock;

    // Tree branches
    std::string branchFile {"v_assets/tree.png"};
    sf::Texture branchTexture;
    load_texture(&branchTexture,branchFile);

    Branch* rect1 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2-200.0f,1000.0f},VIEW_WIDTH);
    Branch* rect2 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2+75.0f,800.0f},VIEW_WIDTH);
    Branch* rect3 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2-200.0f,600.0f},VIEW_WIDTH);
    Branch* rect4 = new Branch(&branchTexture,{350.0f,150.0f},{VIEW_WIDTH/2+50.0f,300.0f},VIEW_WIDTH);
    Branch* rect5 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2-260.0f,150.0f},VIEW_WIDTH);
    
    std::vector<Branch*> rects;
    rects.push_back(rect1);
    rects.push_back(rect2);
    rects.push_back(rect3);
    rects.push_back(rect4);
    rects.push_back(rect5);
    rectsLen = rects.size();

    // Tree trunk pieces
    std::string trunkFile {"v_assets/trunk.png"};
    sf::Texture trunkTexture;
    load_texture(&trunkTexture,trunkFile);
    Trunk* trunk1 = new Trunk(&trunkTexture,{100.0f,300.0f},{575.0f,800.0f});
    Trunk* trunk2 = new Trunk(&trunkTexture,{100.0f,300.0f},{585.0f,500.0f});
    Trunk* trunk3 = new Trunk(&trunkTexture,{100.0f,300.0f},{575.0f,200.0f});
    Trunk* trunk4 = new Trunk(&trunkTexture,{100.0f,300.0f},{585.0f,-100.0f});
    std::vector<Trunk*> trunks;
    trunks.push_back(trunk1);
    trunks.push_back(trunk2);
    trunks.push_back(trunk3);
    trunks.push_back(trunk4);

    // Music notes
    std::string noteFile {"v_assets/note.png"};
    sf::Texture noteTexture;
    load_texture(&noteTexture,noteFile);
    Note* note1 = new Note(&noteTexture,{30.0f,50.0f},{700.0f,970.0f});
    Note* note2 = new Note(&noteTexture,{30.0f,50.0f},{430.0f,770.0f});
    std::vector<Note*> notes;
    notes.push_back(note1);
    notes.push_back(note2);

    // main player & its arms
    std::string armFile {"v_assets/arm.png"};
    sf::Texture armTexture;
    load_texture(&armTexture,armFile);
    std::string unicornFile {"v_assets/unicorn.png"};
    sf::Texture unicornTexture;
    load_texture(&unicornTexture,unicornFile);
    Player* player_arm = new Player(&armTexture,{0.0f,30.0f},{600.0f,1100.0f},900.0f,true);
    Player* main_player = new Player(&unicornTexture,{100.0f,100.0f},{600.0f,1100.0f},100.0f,false);
    // Player* player_bird = new Player({50.0f,50.0f},{370.0f,900.0f},500.0f,false);
    std::vector<Player*> players;
    players.push_back(player_arm);
    players.push_back(main_player);

    // game loop
    while (window.isOpen()){

        deltaTime = clock.restart().asSeconds();
        totalTime += deltaTime;
        view.setCenter(VIEW_WIDTH/2,main_player->getPosition().y-100.0f);
        view.setSize(800.0f,800.0f);
        
        // this part handles events related to the actual game window like closing or resizing. 
        sf::Event evnt;
        while(window.pollEvent(evnt)){
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                resizedView(window,view,VIEW_WIDTH);
                printf("New window width: %i New window height: %i\n", evnt.size.width, evnt.size.height);
                break;
            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Escape)
                        window.close();
                if (evnt.key.code == sf::Keyboard::R)
                    game(window,view,HUD,VIEW_WIDTH);
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
                plr->ifClickToRight();
                plr->Rotate();
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
        
        
        for (auto rect: rects){
            for (auto plr: players){
                if(rect->Collision(plr->getClickPos(),plr->getVelocity().y)){
                    plr->updateState('M');
                    plr->AdjustArm(main_player->getPosition());
                    plr->State(deltaTime);
                    plr->Draw(window);
                    break;
                }else{
                    plr->updateState('S');
                    plr->AdjustArm(main_player->getPosition());
                    plr->State(deltaTime);
                    plr->Draw(window);
                }
            }
        }

        for (auto note: notes){
            if(i>=rectsLen){
                i=0;
            }
            note->Animate(totalTime);
            if(note->MoveElsewhere(main_player->getPosition(),rects.at(i)->getPosition())){
                ++i;
            };
            note->Draw(window);
        }

        // player_bird->BirdMovement(main_player->getPosition(),deltaTime);
        // player_bird->Animate(main_player->getPosition(),totalTime);
        // player_bird->Draw(window);

        window.display();
    }
}