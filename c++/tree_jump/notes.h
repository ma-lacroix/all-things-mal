// Music notes class

#ifndef _NOTE_H_
#define _NOTE_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "object.h"
#define PI 3.14159265

class Note: public Object {
private:
    sf::RectangleShape shape;
    bool status;
public:
    Note(sf::Texture*, sf::Vector2f,sf::Vector2f);
    ~Note();
    bool MoveElsewhere(sf::Vector2f,sf::Vector2f);
    void updateYcoord(float,sf::Vector2f);
    void Animate(float);
    void Draw(sf::RenderWindow&);
};

Note::Note(sf::Texture* textureFile, sf::Vector2f objectSize, sf::Vector2f position)
    :Object(textureFile,objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setOrigin(objectSize.x/2,objectSize.y/2);
    shape.setFillColor(sf::Color(255,255,255,255));
    shape.setTexture(textureFile);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.0f);
}

Note::~Note(){
}

void Note::Animate(float totalTime){
    float velocity;
    velocity = std::sinf(totalTime*PI)/40;
    shape.move(0.0f,velocity);
}

bool Note::MoveElsewhere(sf::Vector2f plrPos, sf::Vector2f branchPos){
    if(abs(shape.getPosition().x - plrPos.x) < 120.0f &
       abs(shape.getPosition().y - plrPos.y) < 120.0f){
            shape.setPosition(branchPos.x+90.0f,branchPos.y-1200.0f);
            return true;
       }else{
            return false;
       }
}

void Note::updateYcoord(float Ycoord,sf::Vector2f branch1Pos){
    if(shape.getPosition().y-Ycoord > 600.0f){
        shape.move(0.0f,-1200.0f);
    }
}

void Note::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif