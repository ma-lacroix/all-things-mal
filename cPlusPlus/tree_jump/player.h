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
    sf::Vector2f mouseClickPos;
    float speed;
    char playstate;
public:
    // Player(sf::Texture* textureFile,sf::Vector2f PlayerSize, sf::Vector2f position, bool clickable);
    Player(sf::Vector2f, sf::Vector2f);
    ~Player();
    void State(float);
    void Movement(float);
    void Stop();
    void Draw(sf::RenderWindow&);
    void setMouseClickPos(sf::Vector2f newClick) {mouseClickPos = newClick;};
    sf::Vector2f getPosition() {return shape.getPosition();};
    sf::Vector2f getClickPos() {return mouseClickPos;};
    sf::Vector2f getVelocity() {return velocity;};
    void updateState(char newState) {playstate = newState;};
    char getPlaystate() {return playstate;};
};

Player::Player(sf::Vector2f objectSize, sf::Vector2f position)
    :Object(objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    // shape.setOrigin(400.0f,400.0f);
    velocity = {0.0f,0.0f};
    mouseClickPos = {0.0f,0.0f};
    speed = 150.0f;
    playstate = 'S';
}

Player::~Player(){
}

void Player::State(float deltatime){
    switch (playstate){
    case 'M':
        Movement(deltatime);
        shape.setFillColor(sf::Color::Cyan);
        break;
    case 'S':
        Stop();
        shape.setFillColor(sf::Color::Blue);
    default:
        break;
    }
}

void Player::Movement(float deltatime){
    sf::Vector2f direction;
    sf::Vector2f direction_norm;
    direction.x = mouseClickPos.x-(shape.getPosition().x+shape.getSize().x/2);
    direction.y = mouseClickPos.y-(shape.getPosition().y+shape.getSize().y);
    direction_norm = direction / sqrtf(direction.x * direction.x + direction.y * direction.y);
    velocity = direction_norm*deltatime*speed;
    if(abs(direction.x+direction.y)>0.7f){
        shape.move(velocity);
    }else{
        updateState('S');
        mouseClickPos = {0.0f,0.0f};
    }
}

void Player::Stop(){
    shape.setFillColor(sf::Color::Blue);
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif