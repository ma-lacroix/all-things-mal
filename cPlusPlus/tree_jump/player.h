// object class

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "object.h"
#define PI 3.14159265

class Player: public Object {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f mouseClickPos;
    float speed;
    bool arm;
    char playstate;
public:
    // Player(sf::Texture* textureFile,sf::Vector2f PlayerSize, sf::Vector2f position, bool clickable);
    Player(sf::Vector2f,sf::Vector2f,float,bool);
    ~Player();
    void State(float);
    void Rotate();
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

Player::Player(sf::Vector2f objectSize, sf::Vector2f position, float speed, bool arm)
    :Object(objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    this->speed = speed;
    this->arm = arm;
    // shape.setOrigin(400.0f,400.0f);
    velocity = {0.0f,0.0f};
    mouseClickPos = {0.0f,0.0f};
    playstate = 'S';
}

Player::~Player(){
}

void Player::State(float deltatime){
    switch (playstate){
    case 'M':
        shape.setFillColor(sf::Color::Cyan);
        Movement(deltatime);
        break;
    case 'S':
        Stop();
    default:
        break;
    }
}

void Player::Rotate(){
    // Pythagoras theorem to determine angle of shape
    if(arm){
        float a = mouseClickPos.y-shape.getPosition().y;
        float b = mouseClickPos.x-shape.getPosition().x;
        float angle = atanf(a/b)*180/PI;
        printf("angle: %f\n",angle);
        shape.setRotation(angle);
    }
}

void Player::Movement(float deltatime){
    sf::Vector2f direction;
    sf::Vector2f direction_norm;
    direction.x = mouseClickPos.x-(shape.getPosition().x+shape.getSize().x/2);
    direction.y = mouseClickPos.y-(shape.getPosition().y+shape.getSize().y);
    direction_norm = direction / sqrtf(direction.x * direction.x + direction.y * direction.y); // avoid speed changes
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