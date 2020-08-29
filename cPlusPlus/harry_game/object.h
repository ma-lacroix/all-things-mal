// class handling the onscreen objects

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "collider.h"

class Object {
private:
    sf::RectangleShape some_shape;
public:
    Object(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position);
    ~Object();
    void Draw(sf::RenderWindow& window);
    Collider GetCollider() {return Collider(some_shape);};
};

Object::Object(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position){
    some_shape.setSize(objectSize);
    some_shape.setPosition(position);
    some_shape.setTexture(textureFile);
    some_shape.setOutlineThickness(1);
}

Object::~Object(){
}

void Object::Draw(sf::RenderWindow& window){
    window.draw(some_shape);
}

#endif

