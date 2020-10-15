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
    Object(sf::Texture*, sf::Vector2f, sf::Vector2f);
    ~Object();
};

Object::Object(sf::Texture* textureFile, sf::Vector2f objectSize, sf::Vector2f position){
    shape.setOrigin(400.0f,400.0f);
}

Object::~Object(){
}

#endif