#include <SFML/Graphics.hpp>
#include <iostream>
#include "sheet.h"

struct melodyBox
{
    sf::RectangleShape shape;
    sf::Vector2f boxSize;
    sf::Vector2f boxPos;
    melodyBox(sf::Texture*,sf::Vector2f,sf::Vector2f);
    ~melodyBox();
    void Selection(char);
    sf::Vector2f getPosition() {return shape.getPosition();};
};

melodyBox::melodyBox(sf::Texture* textureFile,sf::Vector2f boxSize, sf::Vector2f boxPos){
    shape.setTexture(textureFile);
    shape.setPosition(boxPos);
    shape.setSize(boxSize);
}

melodyBox::~melodyBox(){
}

void melodyBox::Selection(char choice){
    shape.setFillColor(sf::Color(230.0f,255.0f,230.0f,255.0f));
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(8.0f);
}

#ifndef _MENU_H_
#define _MENU_H_

class Menu {
private:
    melodyBox* box1;
    melodyBox* box2;
    melodyBox* box3;
    melodyBox* box4;
    melodyBox* box5;
    Sheet* sheetNotes1;
    Sheet* sheetNotes2;
    Sheet* sheetNotes3;
    Sheet* sheetNotes4;
    Sheet* sheetNotes5;
    std::vector<melodyBox*> boxes;
    std::vector<Sheet*> notes;
public:
    Menu(sf::Texture*,std::vector<sf::Texture*> ,sf::Vector2f,sf::Vector2f);
    ~Menu();
    void Selection(char);
    void Draw(sf::RenderWindow&);
};

Menu::Menu(sf::Texture* textureFile, std::vector<sf::Texture*> noteTextures,sf::Vector2f boxSize, sf::Vector2f boxPos){
    box1 = new melodyBox(textureFile,boxSize,boxPos);
    box2 = new melodyBox(textureFile,boxSize,{boxPos.x,boxPos.y+boxSize.y*1.5f});
    box3 = new melodyBox(textureFile,boxSize,{boxPos.x,boxPos.y+boxSize.y*3.0f});
    box4 = new melodyBox(textureFile,boxSize,{boxPos.x,boxPos.y+boxSize.y*4.5f});
    box5 = new melodyBox(textureFile,boxSize,{boxPos.x,boxPos.y+boxSize.y*6.0f});
    sheetNotes1 = new Sheet(noteTextures,'A',box1->getPosition(),255);
    sheetNotes2 = new Sheet(noteTextures,'B',box2->getPosition(),255);
    sheetNotes3 = new Sheet(noteTextures,'C',box3->getPosition(),255);
    sheetNotes4 = new Sheet(noteTextures,'D',box4->getPosition(),255);
    sheetNotes5 = new Sheet(noteTextures,'E',box5->getPosition(),255);
    boxes.push_back(box1);
    boxes.push_back(box2);
    boxes.push_back(box3);
    boxes.push_back(box4);
    boxes.push_back(box5);
    notes.push_back(sheetNotes1);
    notes.push_back(sheetNotes2);
    notes.push_back(sheetNotes3);
    notes.push_back(sheetNotes4);
    notes.push_back(sheetNotes5);
}   

Menu::~Menu(){
    delete box1;
    delete box2;
    delete box3;
    delete box4;
    delete box5;
    delete sheetNotes1;
    delete sheetNotes2;
    delete sheetNotes3;
    delete sheetNotes4;
    delete sheetNotes5;
    std::cout<<"Deleted boxes from menu"<<std::endl;
}

void Menu::Selection(char choice){
    if(choice == 'A'){
        box1->Selection(choice);
    }
    if(choice == 'B'){
        box2->Selection(choice);
    }
    if(choice == 'C'){
        box3->Selection(choice);
    }
    if(choice == 'D'){
        box4->Selection(choice);
    }
    if(choice == 'E'){
        box5->Selection(choice);
    }
}

void Menu::Draw(sf::RenderWindow& window){
    for(auto box: boxes){
        window.draw(box->shape);
    }
    for(auto note: notes){
        note->Draw(window);
    }
}

#endif