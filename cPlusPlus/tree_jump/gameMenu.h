#include <SFML/Graphics.hpp>
#include <iostream>

struct melodyBox
{
    sf::RectangleShape shape;
    sf::Vector2f boxSize;
    sf::Vector2f boxPos;
    melodyBox(sf::Texture*,sf::Vector2f,sf::Vector2f);
    ~melodyBox();
    void Selection(char);
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
    std::vector<melodyBox*> boxes;
public:
    Menu(sf::Texture*,sf::Vector2f,sf::Vector2f);
    ~Menu();
    void Selection(char);
    void Draw(sf::RenderWindow&);
};

Menu::Menu(sf::Texture* textureFile,sf::Vector2f boxSize, sf::Vector2f boxPos){
    box1 = new melodyBox(textureFile,boxSize,boxPos);
    box2 = new melodyBox(textureFile,boxSize,{boxPos.x,boxPos.y+boxSize.y*1.5f});
    box3 = new melodyBox(textureFile,boxSize,{boxPos.x,boxPos.y+boxSize.y*3.0f});
    box4 = new melodyBox(textureFile,boxSize,{boxPos.x,boxPos.y+boxSize.y*4.5f});
    box5 = new melodyBox(textureFile,boxSize,{boxPos.x,boxPos.y+boxSize.y*6.0f});
    boxes.push_back(box1);
    boxes.push_back(box2);
    boxes.push_back(box3);
    boxes.push_back(box4);
    boxes.push_back(box5);
}

Menu::~Menu(){}

void Menu::Selection(char choice){
    if(choice == 'a'){
        box1->Selection(choice);
    }
    if(choice == 'b'){
        box2->Selection(choice);
    }
    if(choice == 'c'){
        box3->Selection(choice);
    }
    if(choice == 'd'){
        box4->Selection(choice);
    }
    if(choice == 'e'){
        box5->Selection(choice);
    }
}

void Menu::Draw(sf::RenderWindow& window){
    for(auto box: boxes){
        window.draw(box->shape);
    }
}

#endif