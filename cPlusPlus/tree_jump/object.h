// object class

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <SFML/Graphics.hpp>
#include <iostream>

class Object {
private:
    sf::RectangleShape shape;
public:
    Object(sf::Texture*, sf::Vector2f, sf::Vector2f);
    ~Object();
    void Draw(sf::RenderWindow&);
};

Object::Object(sf::Texture* textureFile, sf::Vector2f objectSize, sf::Vector2f position){
    shape.setOrigin(objectSize.x/2,objectSize.y/2);
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setFillColor(sf::Color(255,255,255,255));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(8.0f);
    shape.setTexture(textureFile);
}

Object::~Object(){
}

void Object::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif