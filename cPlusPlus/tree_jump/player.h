// object class

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "object.h"

class Player: public Object {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float speed;
    char playstate;
public:
    // Player(sf::Texture* textureFile,sf::Vector2f PlayerSize, sf::Vector2f position, bool clickable);
    Player(sf::Vector2f, sf::Vector2f);
    ~Player();
    void State(sf::Vector2f,float);
    void Movement(sf::Vector2f,float);
    void Stop();
    void Draw(sf::RenderWindow&);
    sf::Vector2f getPosition() {return shape.getPosition();};
    void updateState(char newState) {playstate = newState;};
    char getPlaystate() {return playstate;};
};

Player::Player(sf::Vector2f objectSize, sf::Vector2f position)
    :Object(objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setOrigin(400.0f,400.0f);
    speed = 200.0f;
    playstate = 'S';
}

Player::~Player(){
}

void Player::State(sf::Vector2f clickPos,float deltatime){
    switch (playstate){
    case 'M':
        Movement(clickPos,deltatime);
        shape.setFillColor(sf::Color::Cyan);
        break;
    case 'S':
        Stop();
        shape.setFillColor(sf::Color::Blue);
    default:
        break;
    }
}

void Player::Movement(sf::Vector2f clickPos,float deltatime){
    sf::Vector2f direction;
    sf::Vector2f direction_norm;
    direction.x = clickPos.x-(shape.getPosition().x+shape.getSize().x/2);
    direction.y = clickPos.y-(shape.getPosition().y+shape.getSize().y);
    direction_norm = direction / sqrtf(direction.x * direction.x + direction.y * direction.y);
    if(abs(direction.x+direction.y)>0.07f){
        shape.move(direction_norm*deltatime*speed);
    }else{
        updateState('S');
    }
}

void Player::Stop(){
    shape.setFillColor(sf::Color::Blue);
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif