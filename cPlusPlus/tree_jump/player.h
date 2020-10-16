// object class

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "object.h"
#define PI 3.14159265

class Player: public Object {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f mouseClickPos;
    sf::Vector2f objectSize;
    float speed;
    float angle;
    bool arm;
    bool clickToRight;
    char playstate;
public:
    // Player(sf::Texture* textureFile,sf::Vector2f PlayerSize, sf::Vector2f position, bool clickable);
    Player(sf::Texture* textureFile, sf::Vector2f,sf::Vector2f,float,bool);
    ~Player();
    void State(float);
    void ifClickToRight();
    void AdjustArm(sf::Vector2f);
    void Animate(sf::Vector2f,float);
    void Rotate();
    void Movement(float);
    void BirdMovement(sf::Vector2f,float);
    void Stop();
    void setMouseClickPos(sf::Vector2f);
    void Draw(sf::RenderWindow&);
    sf::Vector2f getPosition() {return shape.getPosition();};
    sf::Vector2f getClickPos() {return mouseClickPos;};
    sf::Vector2f getVelocity() {return velocity;};
    void updateState(char newState) {playstate = newState;};
    char getPlaystate() {return playstate;};
};

Player::Player(sf::Texture* textureFile, sf::Vector2f objectSize, sf::Vector2f position, float speed, bool arm)
    :Object(textureFile, objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setOrigin(objectSize.x/2,objectSize.y/2);
    this->objectSize = objectSize;
    this->speed = speed;
    this->arm = arm;
    velocity = {0.0f,0.0f};
    mouseClickPos = {0.0f,0.0f};
    playstate = 'S';
    clickToRight = false;
    shape.setTexture(textureFile);
}

Player::~Player(){
}

void Player::State(float deltatime){
    switch (playstate){
    case 'M':
        // shape.setFillColor(sf::Color::Cyan);
        Movement(deltatime);
        break;
    case 'S':
        Stop();
    default:
        break;
    }
}

void Player::ifClickToRight(){    
    if(mouseClickPos.x>shape.getPosition().x){
        clickToRight = true;
    }else{
        clickToRight = false;
    }
}

void Player::AdjustArm(sf::Vector2f Coords){
    if(arm){
    // Pythagoras theorem to determine hypotenuse
        shape.setSize({-abs(sqrtf(powf(shape.getPosition().x-Coords.x,2)+powf(shape.getPosition().y-Coords.y,2))),
                        objectSize.y});
    }
}

void Player::Animate(sf::Vector2f plrPos,float totaltime){
    float velocity1,velocity2;
    velocity1 = std::sinf(totaltime*PI)+5.0f;
    velocity2 = std::sinf(totaltime*PI);
    shape.move(velocity1,-velocity2);
}

void Player::Rotate(){
    // Pythagoras theorem to determine angle of shape using trigonometry
    if(arm){
        float a = mouseClickPos.y-shape.getPosition().y;
        float b = mouseClickPos.x-shape.getPosition().x;
        angle = atanf(a/b)*180/PI;
        if(!clickToRight){
            angle+=180;
        }
        shape.setRotation(angle);
    }
}

void Player::Movement(float deltatime){
    sf::Vector2f direction;
    sf::Vector2f direction_norm;
    direction.x = mouseClickPos.x-(shape.getPosition().x);
    direction.y = mouseClickPos.y-(shape.getPosition().y);
    direction_norm = direction / sqrtf(direction.x * direction.x + direction.y * direction.y); // avoid speed changes
    velocity = direction_norm*deltatime*speed;
    if(abs(direction.x+direction.y)>0.7f){
        shape.move(velocity);
    }else{
        updateState('S');
        mouseClickPos = {0.0f,0.0f};
        velocity = {0.0f,0.0f};
    }
}

void Player::BirdMovement(sf::Vector2f plrPos,float deltatime){
    sf::Vector2f direction;
    sf::Vector2f direction_norm;
    direction.x = plrPos.x+130.0f-(shape.getPosition().x);
    direction.y = plrPos.y-95.0f-(shape.getPosition().y);
    // direction_norm = direction / sqrtf(direction.x * direction.x + direction.y * direction.y); // avoid speed changes
    velocity = direction*deltatime*speed;
    if(abs(direction.x+direction.y)>0.7f){
        shape.move(velocity);
    }else{
        updateState('S');
        mouseClickPos = {0.0f,0.0f};
        velocity = {0.0f,0.0f};
    }
}

void Player::Stop(){
    // shape.setFillColor(sf::Color::Blue);
}

void Player::setMouseClickPos(sf::Vector2f newClick) {
    mouseClickPos = newClick;
    if(arm){
        if(shape.getSize().x <= 5.0f){
            mouseClickPos = newClick;    
        }
    }else{
        if(velocity.x == 0 & velocity.y == 0){
            mouseClickPos = newClick;
        }
    }
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif