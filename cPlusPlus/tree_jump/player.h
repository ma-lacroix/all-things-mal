// object class

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "object.h"

class Player: public Object {
private:
    sf::RectangleShape shape;
public:
    // Player(sf::Texture* textureFile,sf::Vector2f PlayerSize, sf::Vector2f position, bool clickable);
    Player(sf::Vector2f objectSize, sf::Vector2f position);
    ~Player();
    void Draw(sf::RenderWindow&);
};

Player::Player(sf::Vector2f objectSize, sf::Vector2f position)
    :Object(objectSize,position)
    {
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin(400.0f,400.0f);
}

Player::~Player(){
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif