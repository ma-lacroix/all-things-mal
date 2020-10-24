// object class

#ifndef _TRUNK_H_
#define _TRUNK_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "object.h"

class Trunk: public Object {
private:
    sf::RectangleShape shape;
    bool status;
public:
    // Trunk(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, bool clickable);
    Trunk(sf::Texture*, sf::Vector2f,sf::Vector2f);
    ~Trunk();
    void updateYcoord(float);
    void Draw(sf::RenderWindow&);
};

Trunk::Trunk(sf::Texture* textureFile, sf::Vector2f objectSize, sf::Vector2f position)
    :Object(textureFile,objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setFillColor(sf::Color(190,105,30,255));
    shape.setTexture(textureFile);
}

Trunk::~Trunk(){
}

void Trunk::updateYcoord(float Ycoord){
    if(shape.getPosition().y-Ycoord > 600.0f){
        shape.move(0.0f,-1500.0f);
    }
}

void Trunk::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif