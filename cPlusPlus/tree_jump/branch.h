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
    sf::IntRect textureRect;
public:
    // Branch(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, bool clickable);
    Branch(sf::Texture*, sf::Vector2f,sf::Vector2f,float);
    ~Branch();
    void updateColor(bool);
    void updateYcoord(float);
    bool Collision(sf::Vector2f, float);
    void Draw(sf::RenderWindow&);
    bool getStatus() {return status;};
    sf::Vector2f getPosition() {return shape.getPosition();};
};

Branch::Branch(sf::Texture* textureFile, sf::Vector2f objectSize, sf::Vector2f position, float VIEW_WIDTH)
    :Object(textureFile,objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    bool status = false;
    shape.setTexture(textureFile);
    textureRect.width = textureFile->getSize().x;
    textureRect.height = textureFile->getSize().y;
    if(position.x > VIEW_WIDTH/3){
        // textureRect.left,
        textureRect.width = abs(textureRect.width);
    }else{
        textureRect.left = abs(textureRect.width);
        textureRect.width = -abs(textureRect.width);
    }
    shape.setTextureRect(textureRect);
}

Branch::~Branch(){
}

void Branch::updateColor(bool value){
    if(value){
        shape.setFillColor(sf::Color(255,255,255,110));
    }else{
        shape.setFillColor(sf::Color(255,255,255,255));
    }   
}

void Branch::updateYcoord(float Ycoord){
    if(shape.getPosition().y-Ycoord > 500.0f){
        shape.move(0.0f,-1200.0f);
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