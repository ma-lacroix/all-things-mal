// object class

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <SFML/Graphics.hpp>
#include <iostream>

class Object {
private:
    sf::RectangleShape shape;
public:
    // Object(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, bool clickable);
    Object(sf::Vector2f objectSize, sf::Vector2f position);
    ~Object();
    bool clicked;
    void updateColor(sf::Vector2i clickPos);
    void Draw(sf::RenderWindow& window);
};

Object::Object(sf::Vector2f objectSize, sf::Vector2f position){
    shape.setSize(objectSize);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(400.0f,400.0f);
    clicked = false;
    // shape.setTexture(textureFile);
}

Object::~Object(){
}

void Object::updateColor(sf::Vector2i clickPos){
    float lowX = shape.getPosition().x;
    float highX = shape.getPosition().x+shape.getSize().x;
    float lowY = shape.getPosition().y;
    float highY = shape.getPosition().y+shape.getSize().y;

    if(clickPos.x >= lowX & clickPos.x <= highX &
            clickPos.y >= lowY & clickPos.y <= highY){
        shape.setFillColor(sf::Color::White);
    }else{
        shape.setFillColor(sf::Color::Red);
    }
}

void Object::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif