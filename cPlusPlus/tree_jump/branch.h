// Branch class

#ifndef _BRANCH_H_
#define _BRANCH_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "object.h"
#include "player.h"

class Branch: public Object {
private:
    sf::RectangleShape shape;
    bool status;
public:
    // Branch(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, bool clickable);
    Branch(sf::Vector2f,sf::Vector2f);
    ~Branch();
    void updateColor(bool);
    bool Collision(sf::Vector2f, float);
    void Draw(sf::RenderWindow&);
    bool getStatus() {return status;};
    sf::Vector2f getPosition() {return shape.getPosition();};
};

Branch::Branch(sf::Vector2f objectSize, sf::Vector2f position)
    :Object(objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    bool status = false;
}

Branch::~Branch(){
}

void Branch::updateColor(bool value){
    if(value){
        shape.setFillColor(sf::Color(240,20,20,110));
    }else{
        shape.setFillColor(sf::Color(50,100,100,255));
    }
    
}

bool Branch::Collision(sf::Vector2f clickPos, float Yoffset){
    float lowX = shape.getPosition().x;
    float highX = shape.getPosition().x+shape.getSize().x;
    float lowY = shape.getPosition().y;
    float highY = shape.getPosition().y+shape.getSize().y;

    if(clickPos.x >= lowX & clickPos.x <= highX &
            clickPos.y+Yoffset >= lowY & clickPos.y+Yoffset <= highY){
        status = true;
    }else{
        status = false;
    }
    return status;
}

void Branch::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif