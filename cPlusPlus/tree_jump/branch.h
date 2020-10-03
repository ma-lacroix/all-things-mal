// Branch class

#ifndef _BRANCH_H_
#define _BRANCH_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "object.h"

class Branch: public Object {
private:
    sf::RectangleShape shape;
public:
    // Branch(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, bool clickable);
    Branch(sf::Vector2f,sf::Vector2f);
    ~Branch();
    void updateColor(sf::Vector2i);
    void Draw(sf::RenderWindow&);
};

Branch::Branch(sf::Vector2f objectSize, sf::Vector2f position)
    :Object(objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setOrigin(400.0f,400.0f);
}

Branch::~Branch(){
}

void Branch::updateColor(sf::Vector2i clickPos){
    float lowX = shape.getPosition().x;
    float highX = shape.getPosition().x+shape.getSize().x;
    float lowY = shape.getPosition().y;
    float highY = shape.getPosition().y+shape.getSize().y;

    if(clickPos.x >= lowX & clickPos.x <= highX &
            clickPos.y >= lowY & clickPos.y <= highY){
        shape.setFillColor(sf::Color::White);
    }else{
        shape.setFillColor(sf::Color::Green);
    }
}

void Branch::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif