// class handling the onscreen objects

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <SFML/Graphics.hpp>
#include <iostream>

class Object {
private:

public:
    Object(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position);
    ~Object();
    sf::RectangleShape main_sprite;
    void Draw(sf::RenderWindow& window);
};

Object::Object(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position){
    main_sprite.setSize(objectSize);
    main_sprite.setPosition(position);
    main_sprite.setTexture(textureFile);
}

Object::~Object(){
}

void Object::Draw(sf::RenderWindow& window){
    window.draw(main_sprite);
}

#endif

