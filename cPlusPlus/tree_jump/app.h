// struct that initialises the game, renders the game objects and the loop

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include "sheet.h"
#include "branch.h"
#include "notes.h"
#include "trunk.h"
#include "player.h"
#include "sun.h"
#include "gameMenu.h"

struct app{
    void game(sf::Music& main_song,sf::RenderWindow& window,sf::View mainMenu,sf::View view,sf::View HUD,float VIEW_WIDTH);  
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

void app::game(sf::Music& main_song,sf::RenderWindow& window,sf::View mainMenu,sf::View frontview,sf::View HUD,float VIEW_WIDTH){

    // timers
    float deltaTime {0.0f};
    float totalTime {0.0f};
    
    // game globals
    char menuChoice {'n'};
    float Ycoord {0.0f};
    size_t rectsLen {0};
    int i {3};
    int gameOverCounter {0};
    sf::Clock clock;
    std::srand(time(0));
    bool gameOn {false};
    bool menuOn {true};
    bool goal {false};
    bool introMusic {true};
    bool startMusic {true};
    bool endMusic {true};

    // sounds
    sf::Sound intro;
    sf::SoundBuffer buffer1;
    buffer1.loadFromFile("a_assets/intro.wav");
    intro.setBuffer(buffer1);
    intro.setVolume(80);

    sf::Sound Song_A;
    sf::SoundBuffer buffer2;
    buffer2.loadFromFile("a_assets/Song_A.flac");
    Song_A.setBuffer(buffer2);
    Song_A.setVolume(80);

    sf::Sound Song_B;
    sf::SoundBuffer buffer3;
    buffer3.loadFromFile("a_assets/Song_B.flac");
    Song_B.setBuffer(buffer3);
    Song_B.setVolume(80);

    sf::Sound Song_C;
    sf::SoundBuffer buffer4;
    buffer4.loadFromFile("a_assets/Song_C.flac");
    Song_C.setBuffer(buffer4);
    Song_C.setVolume(80);

    sf::Sound Song_D;
    sf::SoundBuffer buffer5;
    buffer5.loadFromFile("a_assets/Song_D.flac");
    Song_D.setBuffer(buffer5);
    Song_D.setVolume(80);

    sf::Sound Song_E;
    sf::SoundBuffer buffer6;
    buffer6.loadFromFile("a_assets/Song_E.flac");
    Song_E.setBuffer(buffer6);
    Song_E.setVolume(80);

    sf::Sound c_scale;
    sf::SoundBuffer buffer7;
    buffer7.loadFromFile("a_assets/c_scale.flac");
    c_scale.setBuffer(buffer7);
    c_scale.setVolume(80);

    sf::Sound ouch;
    sf::SoundBuffer buffer8;
    buffer8.loadFromFile("a_assets/ouch.flac");
    ouch.setBuffer(buffer8);
    ouch.setVolume(40);

    sf::Sound armExtension;
    sf::SoundBuffer buffer9;
    buffer9.loadFromFile("a_assets/Vijouit.flac");
    armExtension.setBuffer(buffer9);
    armExtension.setVolume(10);
    armExtension.setPitch(1.1f);

    sf::Sound Monster;
    sf::SoundBuffer buffer10;
    buffer10.loadFromFile("a_assets/Monster.flac");
    Monster.setBuffer(buffer10);
    Monster.setVolume(80);
    Monster.setPitch(0.8f);

    sf::Sound Ding;
    sf::SoundBuffer buffer11;
    buffer11.loadFromFile("a_assets/Ding.flac");
    Ding.setBuffer(buffer11);
    Ding.setVolume(80);
    Ding.setPitch(1.4f);

    std::vector<sf::Sound> sounds;
    sounds.push_back(intro);
    sounds.push_back(Song_A);
    sounds.push_back(Song_B);
    sounds.push_back(Song_C);
    sounds.push_back(Song_D);
    sounds.push_back(Song_E);
    sounds.push_back(c_scale);
    sounds.push_back(ouch);
    sounds.push_back(armExtension);
    sounds.push_back(Monster);
    sounds.push_back(Ding);

    // Menu background
    std::string backgroundFile {"v_assets/background.jpg"};
    sf::Texture backgroundTexture;
    load_texture(&backgroundTexture,backgroundFile);
    Object* menuBackground = new Object(&backgroundTexture,{VIEW_WIDTH/2.0f,VIEW_WIDTH/1.8f},{VIEW_WIDTH/4,VIEW_WIDTH*1.2f});

    // Tree branches
    std::string branchFile {"v_assets/tree.png"};
    sf::Texture branchTexture;
    load_texture(&branchTexture,branchFile);
    Branch* rect1 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2-200.0f,2000.0f},VIEW_WIDTH);
    Branch* rect2 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2+75.0f,1800.0f},VIEW_WIDTH);
    Branch* rect3 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2-200.0f,1600.0f},VIEW_WIDTH);
    Branch* rect4 = new Branch(&branchTexture,{350.0f,150.0f},{VIEW_WIDTH/2+50.0f,1300.0f},VIEW_WIDTH);
    Branch* rect5 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2-260.0f,1150.0f},VIEW_WIDTH);
    Branch* rect6 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2-200.0f,1000.0f},VIEW_WIDTH);
    Branch* rect7 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2+75.0f,800.0f},VIEW_WIDTH);
    Branch* rect8 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2-200.0f,600.0f},VIEW_WIDTH);
    Branch* rect9 = new Branch(&branchTexture,{350.0f,150.0f},{VIEW_WIDTH/2+41.0f,300.0f},VIEW_WIDTH);
    Branch* rect10 = new Branch(&branchTexture,{250.0f,150.0f},{VIEW_WIDTH/2-240.0f,150.0f},VIEW_WIDTH);

    std::vector<Branch*> rects;
    rects.push_back(rect1);
    rects.push_back(rect2);
    rects.push_back(rect3);
    rects.push_back(rect4);
    rects.push_back(rect5);
    rects.push_back(rect6);
    rects.push_back(rect7);
    rects.push_back(rect8);
    rects.push_back(rect9);
    rects.push_back(rect10);
    rectsLen = rects.size();

    // Tree trunk pieces
    std::string trunkFile {"v_assets/trunk.png"};
    sf::Texture trunkTexture;
    load_texture(&trunkTexture,trunkFile);
    Trunk* trunk1 = new Trunk(&trunkTexture,{100.0f,300.0f},{VIEW_WIDTH/2,2100.0f});
    Trunk* trunk2 = new Trunk(&trunkTexture,{100.0f,300.0f},{VIEW_WIDTH/2+15.0f,1800.0f});
    Trunk* trunk3 = new Trunk(&trunkTexture,{100.0f,300.0f},{VIEW_WIDTH/2,1500.0f});
    Trunk* trunk4 = new Trunk(&trunkTexture,{100.0f,300.0f},{VIEW_WIDTH/2-15.0f,1200.0f});
    Trunk* trunk5 = new Trunk(&trunkTexture,{100.0f,300.0f},{VIEW_WIDTH/2,900.0f});
    Trunk* trunk6 = new Trunk(&trunkTexture,{100.0f,300.0f},{VIEW_WIDTH/2,600.0f});
    Trunk* trunk7 = new Trunk(&trunkTexture,{100.0f,300.0f},{VIEW_WIDTH/2,300.0f});
    std::vector<Trunk*> trunks;
    trunks.push_back(trunk1);
    trunks.push_back(trunk2);
    trunks.push_back(trunk3);
    trunks.push_back(trunk4);
    trunks.push_back(trunk5);
    trunks.push_back(trunk6);
    trunks.push_back(trunk7);

    // Music sheet
    std::string sheetFile {"v_assets/sheet.png"};
    sf::Texture sheetTexture;
    load_texture(&sheetTexture,sheetFile);
    Object* sheetBackground = new Object(&sheetTexture,{500.0f,88.0f},{VIEW_WIDTH/3.5f-250.0f,VIEW_WIDTH/2.5f});

    // Friends
    std::string airbaloonFile {"v_assets/airbaloon.png"};
    sf::Texture airbaloonTexture;
    load_texture(&airbaloonTexture,airbaloonFile);
    std::string buddyFile {"v_assets/buddy.png"};
    sf::Texture buddyTexture;
    load_texture(&buddyTexture,buddyFile);
    std::string unicornFile {"v_assets/unicorn.png"};
    sf::Texture unicornTexture;
    load_texture(&unicornTexture,unicornFile);
    std::string flowerFile {"v_assets/flower.png"};
    sf::Texture flowerTexture;
    load_texture(&flowerTexture,flowerFile);
    std::string flowerFile2 {"v_assets/flower2.png"};
    sf::Texture flowerTexture2;
    load_texture(&flowerTexture2,flowerFile2);
    Object* buddy0 = new Object(&airbaloonTexture,{100.0f,220.0f},{rect1->getPosition().x-VIEW_WIDTH*0.2f,5000.0f});
    Object* buddy1 = new Object(&buddyTexture,{250.0f,250.0f},{rect3->getPosition().x-50.0f,rect10->getPosition().y+500.0f});
    Object* buddy2 = new Object(&unicornTexture,{260.0f,200.0f},{rect1->getPosition().x,-3000.0f});
    Object* buddy3 = new Object(&flowerTexture,{250.0f,500.0f},{VIEW_WIDTH/15.0f,VIEW_WIDTH*1.9f});
    Object* buddy4 = new Object(&flowerTexture2,{200.0f,600.0f},{VIEW_WIDTH/3.0f,VIEW_WIDTH*1.9f});
    Object* buddy5 = new Object(&flowerTexture,{300.0f,800.0f},{VIEW_WIDTH/2.0f,VIEW_WIDTH*1.8f});
    Object* buddy6 = new Object(&flowerTexture2,{200.0f,600.0f},{VIEW_WIDTH/1.4f,VIEW_WIDTH*1.9f});
    buddy0->setNoLine();
    buddy1->setNoLine();
    buddy2->setNoLine();
    buddy3->setNoLine();
    buddy4->setNoLine();
    buddy5->setNoLine();
    buddy6->setNoLine();

    // block of grass in background
    sf::RectangleShape grass;
    grass.setFillColor(sf::Color(10,160,80,100));
    grass.setSize({VIEW_WIDTH*1.5f,VIEW_WIDTH*1.5f});
    grass.setPosition({rect1->getPosition().x*0.1f,rect1->getPosition().y});

    // Music notes
    std::string quarterNoteFile {"v_assets/quarterNote.png"};
    sf::Texture quarterNoteTexture;
    load_texture(&quarterNoteTexture,quarterNoteFile);
    std::string eightNoteFile {"v_assets/eightNote.png"};
    sf::Texture eightNoteTexture;
    load_texture(&eightNoteTexture,eightNoteFile);
    std::string halfNoteFile {"v_assets/halfNote.png"};
    sf::Texture halfNoteTexture;
    load_texture(&halfNoteTexture,halfNoteFile);
    std::string emptyNoteFile {"v_assets/emptyNote.png"};
    sf::Texture emptyNoteTexture;
    load_texture(&emptyNoteTexture,emptyNoteFile);
    Note* note1 = new Note(&quarterNoteTexture,{45.0f,70.0f},{rect6->getPosition().x+0.0f,rect6->getPosition().y-5.0f});
    Note* note2 = new Note(&halfNoteTexture,{45.0f,70.0f},{rect2->getPosition().x+200.0f,rect2->getPosition().y-5.0f});
    std::vector<Note*> notes;
    
    // Music notes textures vector
    std::vector<sf::Texture*>  noteTextures;
    notes.push_back(note1);
    notes.push_back(note2);
    noteTextures.push_back(&quarterNoteTexture);
    noteTextures.push_back(&halfNoteTexture);
    noteTextures.push_back(&emptyNoteTexture);
    // noteTextures.push_back(&eightNoteTexture);
    Sheet* sheetNotes = new Sheet(noteTextures,sheetBackground->getPosition(),0);

    // Main menu
    std::string lettersFile {"v_assets/keys.png"};
    sf::Texture lettersTexture;
    load_texture(&lettersTexture,lettersFile);
    Menu* menu = new Menu(&sheetTexture,noteTextures,&lettersTexture,{500.0f,88.0f},{VIEW_WIDTH/3.5f,VIEW_WIDTH*1.2f});

    // main player & its arms
    std::string armFile {"v_assets/arm.png"};
    sf::Texture armTexture;
    load_texture(&armTexture,armFile);
    std::string foxFile {"v_assets/fox.png"};
    sf::Texture foxTexture;
    load_texture(&foxTexture,foxFile);
    Player* player_arm = new Player(&armTexture,{0.0f,40.0f},{rect1->getPosition()},900.0f,true,sounds);
    Player* main_player = new Player(&foxTexture,{150.0f,190.0f},{rect1->getPosition()},300.0f,false,sounds);
    std::vector<Player*> players;
    players.push_back(player_arm);
    players.push_back(main_player);

    std::string sunFile {"v_assets/sun.png"};
    sf::Texture sunTexture;
    load_texture(&sunTexture,sunFile);
    Sun* sun = new Sun(&sunTexture,{150.0f,150.0f},{rect10->getPosition()},50.0f);

    // game loop
    while (window.isOpen()){

        deltaTime = clock.restart().asSeconds();
        totalTime += deltaTime;
        mainMenu.setCenter(VIEW_WIDTH/2,main_player->getPosition().y-100.0f);
        frontview.setCenter(VIEW_WIDTH/2,main_player->getPosition().y-100.0f);        
        // frontview.setSize(800.0f,800.0f);
        frontview.setSize(950.0f,950.0f);

        // this part handles events related to the game window like closing or resizing. 
        sf::Event evnt;
        while(window.pollEvent(evnt)){
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                resizedView(window,frontview,VIEW_WIDTH);
                printf("New window width: %i New window height: %i\n", evnt.size.width, evnt.size.height);
                break;
            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Escape)
                        window.close();
                if (evnt.key.code == sf::Keyboard::R)
                    game(main_song,window,mainMenu,frontview,HUD,VIEW_WIDTH);
                break;
            default:
                break;
            }
        }
        
        window.clear(sf::Color(180,225,255));

        if(menuOn){
            // starts the game,draws the menu until player makes their choice
            if(introMusic){
                introMusic = false;
                c_scale.play();
            }
            window.setView(mainMenu);
            menuBackground->Draw(window);
            menu->Draw(window);
            
            // flowers animations
            buddy3->Animate(totalTime*1.2f,true);
            buddy4->Animate(totalTime,true);
            buddy5->Animate(totalTime*1.7f,false);
            buddy6->Animate(totalTime*2.0f,true);
            buddy3->Draw(window);
            buddy4->Draw(window);
            buddy5->Draw(window);
            buddy6->Draw(window);

            if(menuChoice == 'n'){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    menuChoice = 'A';
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
                    menuChoice = 'B';
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                    menuChoice = 'C';
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    menuChoice = 'D';
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                    menuChoice = 'E';
                }
            }else{
                menu->Selection(menuChoice);
                if(gameOverCounter<400){
                    // little delay before starting the game
                    ++gameOverCounter;
                }else{
                    menuOn = false;
                    gameOn = true;
                    menu->~Menu();
                }
            }
        }else{
            // the main game 

            if(gameOn & !goal){
            
            if(startMusic){
                // stop the intro music
                c_scale.stop();
                startMusic = false;
                main_song.play();
            }

            window.setView(frontview);
            Ycoord = frontview.getCenter().y;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                buddy0->setMouseClickY(window.mapPixelToCoords(sf::Mouse::getPosition(window)).y);
                for (auto plr: players){
                    plr->setMouseClickPos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                    plr->ifClickToRight();
                    plr->Rotate();
                }
            }
            window.draw(grass); 
            buddy0->Animate(totalTime*1.4f,true);
            buddy0->Movement(deltaTime);
            buddy0->Draw(window);
            
            for (auto trunk: trunks){
                trunk->updateYcoord(Ycoord);
                trunk->Draw(window);
            }
            
            for (auto rect: rects){
                rect->updateYcoord(Ycoord);
                rect->updateColor(rect->Collision(main_player->getClickPos(),main_player->getVelocity().y));
                rect->Draw(window);
            }

            // handle the sun ennemy
            sun->setPlayerPos(main_player->getPosition());
            sun->Movement(deltaTime,Ycoord);
            
            // play a sound when sun is close to player
            float distSunPlayer = abs(sun->getPosition().y-main_player->getPosition().y);
            if(distSunPlayer<=603.0f & distSunPlayer >= 595.0f){
                Monster.play();
            }
            if(sun->Collision(main_player->getPosition())){
                if(gameOverCounter<800){
                    main_player->inDanger(true);
                    sun->Draw(window);
                    ++gameOverCounter;
                }else{
                    gameOn = false;
                }
            }else{
                main_player->inDanger(false);
                sun->Draw(window);
            }
            
            for (auto rect: rects){
                for (auto plr: players){
                    if(rect->Collision(plr->getClickPos(),plr->getVelocity().y)){
                        // if click matches a branch position
                        plr->updateState('M');
                        plr->AdjustArm(main_player->getPosition());
                        plr->State(deltaTime,menuChoice);
                        plr->Draw(window);
                        break;
                    }else{
                        plr->updateState('S');
                        plr->Animate(totalTime);
                        plr->AdjustArm(main_player->getPosition());
                        plr->State(deltaTime,menuChoice);
                        plr->Draw(window);
                    }
                }
            }

            for (auto note: notes){
                note->updateYcoord(Ycoord,rect1->getPosition());
                int randNum = rand()%rectsLen+1;
                if(i>=rectsLen){
                    i=0;
                }
                note->Animate(totalTime);
                if(note->MoveElsewhere(main_player->getPosition(),rects.at(i)->getPosition())){
                    // if main player sprite touches a note
                    Ding.play();
                    if(sheetNotes->AddNote()==8){
                        goal = true;
                    };
                    if (randNum+i > rectsLen){ // this avoids having notes appear below
                        i = randNum+i - rectsLen;
                    }else{
                        i+=randNum;
                    }
                    
                };
                note->Draw(window);
            }
            window.setView(HUD);
            sheetBackground->Draw(window);
            sheetNotes->Draw(window);
        }else if(goal){
            // animation when player wins
            main_song.stop();
            window.setView(frontview);
            Ycoord = frontview.getCenter().y;
            menuBackground->moveCenter(frontview.getCenter());
            menuBackground->setTransparency(150);
            menuBackground->Draw(window);
            if(gameOverCounter<1000){
                buddy0->moveCenter(frontview.getCenter()/0.95f);
                ++gameOverCounter;
            }else{
                buddy0->Animate(totalTime*0.1f,true);
                main_player->updateState('F');
                main_player->State(deltaTime,menuChoice);
                buddy0->Draw(window);
                main_player->Draw(window);
            }
        }else{
            // animation when player loses the game
            main_song.stop();
            window.setView(frontview);
            Ycoord = frontview.getCenter().y;
            int incr = 0;

            for (auto trunk: trunks){
                trunk->updateYcoord(Ycoord);
                trunk->GameOver(deltaTime,incr);
                trunk->Draw(window);
                ++incr;
            }
            incr = 0;
            for (auto rect: rects){
                rect->updateYcoord(Ycoord);
                rect->GameOver(deltaTime,incr);
                rect->Draw(window);
                ++incr;
            }

            main_player->updateState('G');
            main_player->State(deltaTime,menuChoice);
            main_player->Draw(window);
        }
    }
        window.display();
    }
}