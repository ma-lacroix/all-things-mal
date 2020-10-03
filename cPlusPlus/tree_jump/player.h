// object class

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "object.h"

class Player: public Object {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float speed;
public:
    // Player(sf::Texture* textureFile,sf::Vector2f PlayerSize, sf::Vector2f position, bool clickable);
    Player(sf::Vector2f, sf::Vector2f);
    ~Player();
    void Draw(sf::RenderWindow&);
    void State(char,sf::Vector2i clickPos,float deltatime);
    void Movement(sf::Vector2i,float deltatime);
    void Stop();
};

Player::Player(sf::Vector2f objectSize, sf::Vector2f position)
    :Object(objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin(400.0f,400.0f);
    speed = 20.0f;
}

Player::~Player(){
}

void Player::State(char state,sf::Vector2i clickPos,float deltatime){
    switch (state){
    case 'M':
        Movement(clickPos,deltatime);
        break;
    case 'S':
        Stop();
    default:
        break;
    }
}

void Player::Movement(sf::Vector2i clickPos,float deltatime){
    velocity.x = -float(clickPos.x)*speed;
    velocity.y = -float(clickPos.y)*speed;
    shape.setFillColor(sf::Color::Cyan);
    shape.move(velocity*deltatime);
}

void Player::Stop(){
    shape.setFillColor(sf::Color::Blue);
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif