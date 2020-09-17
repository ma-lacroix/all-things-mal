// class handling the onscreen objects

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "collider.h"

class Object {
private:
    sf::RectangleShape some_shape;
    bool clipping;
public:
    Object(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, bool clipping);
    ~Object();
    void Draw(sf::RenderWindow& window);
    bool Clipping() {return clipping;};
    sf::RectangleShape GetRect() {return some_shape;};
    Collider GetCollider() {return Collider(some_shape);};
};

Object::Object(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, bool clipping){
    some_shape.setSize(objectSize);
    some_shape.setPosition(position);
    some_shape.setTexture(textureFile);
    this-> clipping = clipping;
    // some_shape.setOutlineThickness(1); // for collision debugging
}

Object::~Object(){
}

void Object::Draw(sf::RenderWindow& window){
    window.draw(some_shape);
}

#endif

