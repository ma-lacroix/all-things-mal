#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#ifndef _SHEET_H_
#define _SHEET_H_

class Sheet {
private:
    sf::RectangleShape note1;
    sf::RectangleShape note2;
    sf::RectangleShape note3;
    sf::RectangleShape note4;
    sf::RectangleShape note5;
    sf::RectangleShape note6;
    sf::RectangleShape note7;
    sf::RectangleShape note8;
    std::vector<sf::RectangleShape*> notes;
    std::vector<sf::Vector2f> sheetA;
    std::vector<sf::Vector2f> sheetB;
    std::vector<sf::Vector2f> sheetC;
    std::vector<sf::Vector2f> sheetD;
    std::vector<sf::Vector2f> sheetE;
    std::vector<int> sheetAindex;
    std::vector<int> sheetBindex;
    std::vector<int> sheetCindex;
    std::vector<int> sheetDindex;
    std::vector<int> sheetEindex;
    std::vector<std::vector<sf::Vector2f>> sheets;
    int index;
    int transparency;
    float startPosX;
    float intervX;
    float startPosY;
    float intervY;
    char code; 

public:
    Sheet(std::vector<sf::Texture*>, char, sf::Vector2f, int);
    Sheet(std::vector<sf::Texture*>, sf::Vector2f, int);
    ~Sheet();
    void drawNotes(char,std::vector<sf::Texture*>);
    void AddNote();
    void Draw(sf::RenderWindow&);
};

Sheet::Sheet(std::vector<sf::Texture*> textures, char code, sf::Vector2f sheetPos, int transparency){
// overloaded consctuctor for menu
    this->transparency = transparency;
    this->code = code;
    index = 0;
    intervX = 50.0f;
    intervY = 5.7f;
    startPosX = sheetPos.x*1.07f;
    startPosY = -sheetPos.y-2*intervY;
    drawNotes(code,textures);
}

Sheet::Sheet(std::vector<sf::Texture*> textures, sf::Vector2f sheetPos, int transparency){
// overloaded consctuctor for game
    this->transparency = transparency;
    code = 'A';
    index = 0;
    intervX = 50.0f;
    intervY = 5.7f;
    startPosX = sheetPos.x*1.07f;
    startPosY = -sheetPos.y-2*intervY;
    drawNotes(code,textures);
}

void Sheet::drawNotes(char code,std::vector<sf::Texture*> textures){
// contains note positions on the music sheet

    notes.push_back(&note1);
    notes.push_back(&note2);
    notes.push_back(&note3);
    notes.push_back(&note4);
    notes.push_back(&note5);
    notes.push_back(&note6);
    notes.push_back(&note7);
    notes.push_back(&note8);

    sheetA.push_back({startPosX+intervX,-(startPosY-(intervY*4))});
    sheetA.push_back({startPosX+intervX*2,-(startPosY-(intervY*4))});
    sheetA.push_back({startPosX+intervX*3,-(startPosY+(intervY*1))});
    sheetA.push_back({startPosX+intervX*4,-(startPosY+(intervY*1))});
    sheetA.push_back({startPosX+intervX*5,-(startPosY-(intervY*4))});
    sheetA.push_back({startPosX+intervX*6,-(startPosY-(intervY*4))});
    sheetA.push_back({startPosX+intervX*7,-(startPosY-(intervY*0))});
    sheetA.push_back({startPosX+intervX*8,-(startPosY-(intervY*0))});
    sheetAindex = {1,2,0,0,1,2,0,0};

    sheetB.push_back({startPosX+intervX,-(startPosY+(intervY*1))});
    sheetB.push_back({startPosX+intervX*2,-(startPosY+(intervY*1))});
    sheetB.push_back({startPosX+intervX*3,-(startPosY-(intervY*1))});
    sheetB.push_back({startPosX+intervX*4,-(startPosY-(intervY*4))});
    sheetB.push_back({startPosX+intervX*5,-(startPosY+(intervY*4))});
    sheetB.push_back({startPosX+intervX*6,-(startPosY+(intervY*4))});
    sheetB.push_back({startPosX+intervX*7,-(startPosY+(intervY*2))});
    sheetB.push_back({startPosX+intervX*8,-(startPosY+(intervY*0))});
    sheetBindex = {0,0,0,0,1,2,0,0};
    
    sheetC.push_back({startPosX+intervX,-(startPosY+(intervY*2))});
    sheetC.push_back({startPosX+intervX*2,-(startPosY+(intervY*2))});
    sheetC.push_back({startPosX+intervX*3,-(startPosY+(intervY*0))});
    sheetC.push_back({startPosX+intervX*4,-(startPosY+(intervY*1))});
    sheetC.push_back({startPosX+intervX*5,-(startPosY+(intervY*0))});
    sheetC.push_back({startPosX+intervX*6,-(startPosY-(intervY*0))});
    sheetC.push_back({startPosX+intervX*7,-(startPosY-(intervY*0))});
    sheetC.push_back({startPosX+intervX*8,-(startPosY+(intervY*0))});
    sheetCindex = {1,2,0,0,1,2,0,0};

    sheetD.push_back({startPosX+intervX,-(startPosY+(intervY*3))});
    sheetD.push_back({startPosX+intervX*2,-(startPosY+(intervY*1))});
    sheetD.push_back({startPosX+intervX*3,-(startPosY+(intervY*3))});
    sheetD.push_back({startPosX+intervX*4,-(startPosY+(intervY*3))});
    sheetD.push_back({startPosX+intervX*5,-(startPosY+(intervY*3))});
    sheetD.push_back({startPosX+intervX*6,-(startPosY-(intervY*1))});
    sheetD.push_back({startPosX+intervX*7,-(startPosY-(intervY*3))});
    sheetD.push_back({startPosX+intervX*8,-(startPosY+(intervY*3))});
    sheetDindex = {0,0,0,0,0,0,0,0};

    sheetE.push_back({startPosX+intervX,-(startPosY+(intervY*5))});
    sheetE.push_back({startPosX+intervX*2,-(startPosY+(intervY*5))});
    sheetE.push_back({startPosX+intervX*3,-(startPosY+(intervY*5))});
    sheetE.push_back({startPosX+intervX*4,-(startPosY+(intervY*5))});
    sheetE.push_back({startPosX+intervX*5,-(startPosY+(intervY*5))});
    sheetE.push_back({startPosX+intervX*6,-(startPosY-(intervY*1))});
    sheetE.push_back({startPosX+intervX*7,-(startPosY-(intervY*2))});
    sheetE.push_back({startPosX+intervX*8,-(startPosY+(intervY*0))});
    sheetEindex = {1,2,1,2,0,0,0,0};

    int i {0};
    switch (code)
    {
    case 'A':
        for(auto note: notes){
            note->setPosition(sheetA.at(i));
            note->setSize({25.0f,45.0f});
            note->setTexture(textures.at(sheetAindex.at(i)));
            note->setFillColor(sf::Color(255,255,255,transparency));
            ++i; 
        }
        break;
    case 'B':
        for(auto note: notes){
            note->setPosition(sheetB.at(i));
            note->setSize({25.0f,45.0f});
            note->setTexture(textures.at(sheetBindex.at(i)));
            note->setFillColor(sf::Color(255,255,255,transparency));
            ++i; 
        }
        break;
    case 'C':
        for(auto note: notes){
            note->setPosition(sheetC.at(i));
            note->setSize({25.0f,45.0f});
            note->setTexture(textures.at(sheetCindex.at(i)));
            note->setFillColor(sf::Color(255,255,255,transparency));
            ++i; 
        }
        break;
    case 'D':
        for(auto note: notes){
            note->setPosition(sheetD.at(i));
            note->setSize({25.0f,45.0f});
            note->setTexture(textures.at(sheetDindex.at(i)));
            note->setFillColor(sf::Color(255,255,255,transparency));
            ++i; 
        }
        break;
    case 'E':
        for(auto note: notes){
            note->setPosition(sheetE.at(i));
            note->setSize({25.0f,45.0f});
            note->setTexture(textures.at(sheetAindex.at(i)));
            note->setFillColor(sf::Color(255,255,255,transparency));
            ++i; 
        }
        break;
    default:
        break;
    }
}

Sheet::~Sheet(){
}

void Sheet::AddNote(){
    if(index < 8){
        notes.at(index)->setFillColor(sf::Color(255,255,255,255));
        ++index;
    }
}

void Sheet::Draw(sf::RenderWindow& window){
    for(auto note: notes){
        window.draw(*note);
    }
}

#endif