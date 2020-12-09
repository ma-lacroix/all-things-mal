// tree trunk objects class

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
    Trunk(sf::Texture*, sf::Vector2f,sf::Vector2f);
    ~Trunk();
    void GameOver(float, int);
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
    float distance = shape.getPosition().y-Ycoord;
    if(distance >= 600.0f){
        shape.move(0.0f,-1800.0f);
    }
}

void Trunk::GameOver(float deltatime, int i){
    shape.setOrigin(shape.getSize().x/2,shape.getSize().y/2);
    shape.rotate(sinf(i)/10);
    shape.move(sinf(i)/100,(500.0f+i*5)*deltatime);
}

void Trunk::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif