// object class

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
    // Note(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, bool clickable);
    Note(sf::Vector2f,sf::Vector2f);
    ~Note();
    bool MoveElsewhere(sf::Vector2f,sf::Vector2f);
    void Animate(float);
    void Draw(sf::RenderWindow&);
};

Note::Note(sf::Vector2f objectSize, sf::Vector2f position)
    :Object(objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setOrigin(objectSize.x/2,objectSize.y/2);
    shape.setFillColor(sf::Color(255,0,0,200));
}

Note::~Note(){
}

void Note::Animate(float totalTime){
    float velocity;
    velocity = std::sin(totalTime*PI)/40;
    shape.move(0.0f,velocity);
}

bool Note::MoveElsewhere(sf::Vector2f plrPos, sf::Vector2f branchPos){
    if(abs(shape.getPosition().x - plrPos.x) < 75.0f &
       abs(shape.getPosition().y - plrPos.y) < 75.0f){
            shape.setPosition(branchPos.x+90.0f,branchPos.y-45.0f);
            return true;
       }else{
            return false;
       }
}

void Note::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif