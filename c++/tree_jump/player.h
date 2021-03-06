// Player class

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <vector>
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
    bool playFinal;
    bool dangerNoise;
    std::vector<sf::Sound> sounds; 
public:
    Player(sf::Texture* textureFile, sf::Vector2f,sf::Vector2f,float,bool,std::vector<sf::Sound>);
    ~Player();
    void State(float,char);
    void ifClickToRight();
    void AdjustArm(sf::Vector2f);
    void Animate(float);
    void Rotate();
    void Movement(float);
    void BirdMovement(sf::Vector2f,float);
    void Stop();
    void setMouseClickPos(sf::Vector2f);
    void inDanger(bool);
    void GameOver(float);
    void Goal(float,char);
    void Draw(sf::RenderWindow&);
    void updateState(char newState) {playstate = newState;};
    sf::Vector2f getPosition() {return shape.getPosition();};
    sf::Vector2f getClickPos() {return mouseClickPos;};
    sf::Vector2f getVelocity() {return velocity;};
    char getPlaystate() {return playstate;};
};

Player::Player(sf::Texture* textureFile, sf::Vector2f objectSize, sf::Vector2f position, float speed, 
                bool arm, std::vector<sf::Sound> sounds)
    :Object(textureFile, objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setOrigin(objectSize.x/2,objectSize.y/2);
    this->objectSize = objectSize;
    this->speed = speed;
    this->arm = arm;
    this->sounds = sounds;
    velocity = {0.0f,0.0f};
    mouseClickPos = {0.0f,0.0f};
    playstate = 'S';
    clickToRight = false;
    playFinal = true;
    dangerNoise = true;
    shape.setTexture(textureFile);
}

Player::~Player(){
}

void Player::State(float deltatime, char menuChoice){
    switch (playstate){
    case 'M':
        Movement(deltatime);
        break;
    case 'S':
        Stop();
        break;
    case 'G':
        GameOver(deltatime);
        break;
    case 'F':
        Goal(deltatime,menuChoice);
        break;
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

void Player::Animate(float totaltime){
    float velocity;
    velocity = std::sinf(totaltime*PI)/250.0f;
    shape.move(-velocity,0.0f);
}

void Player::Rotate(){
    // Pythagoras theorem to determine angle of shape using trigonometry
    if(arm){
        if(abs(shape.getSize().x) < 20.0f){
            float a = mouseClickPos.y-shape.getPosition().y;
            float b = mouseClickPos.x-shape.getPosition().x;
            angle = atanf(a/b)*180/PI;
            if(!clickToRight){
                angle+=180;
            }
            shape.setRotation(angle);
        }
    }else{
        float a = mouseClickPos.y-shape.getPosition().y;
        float b = mouseClickPos.x-shape.getPosition().x;
        angle = atanf(a/b)*180/PI;
        shape.setRotation(angle);
    }
}

void Player::Movement(float deltatime){
    sf::Vector2f direction;
    sf::Vector2f direction_norm;
    direction.x = mouseClickPos.x-(shape.getPosition().x);
    direction.y = mouseClickPos.y-(shape.getPosition().y);
    direction_norm = direction / sqrtf(direction.x * direction.x + direction.y * direction.y); // smooth out movement
    velocity = direction_norm*deltatime*speed;
    if(abs(direction.x+direction.y)>0.7f){
        shape.move(velocity);
    }else{
        updateState('S');
        mouseClickPos = {0.0f,0.0f};
        velocity = {0.0f,0.0f};
        if(!arm){
            shape.setRotation(0.0f);
        }
    }
}

void Player::Stop(){
    // add sound here - unused class function
}

void Player::inDanger(bool value){
    if(value){
        if(dangerNoise){
            dangerNoise = false;
            sounds.at(7).play();
        }
        shape.setFillColor(sf::Color(160.0f,160.0f,100.0f,160.0f));
    }else{
        dangerNoise = true;
        shape.setFillColor(sf::Color(255.0f,255.0f,255.0f,255.0f));
    }
}

void Player::GameOver(float deltatime){
    if(playFinal){
        playFinal = false;
        sounds.at(0).play();
    }
    shape.setFillColor(sf::Color::Blue);
    shape.rotate(0.2f);
    shape.move(0.0f,400.0f*deltatime);
}

void Player::Goal(float deltatime, char menuChoice){
    if(playFinal){
        playFinal = false;
        switch (menuChoice)
        {
        case 'A':
            sounds.at(1).play();
            break;
        case 'B':
            sounds.at(2).play();
            break;
        case 'C':
            sounds.at(3).play();
            break;
        case 'D':
            sounds.at(4).play();
            break;
        case 'E':
            sounds.at(5).play();
            break;
        default:
            break;
        }
    }
    shape.setFillColor(sf::Color::Cyan);
    Animate(deltatime*3.0f);
}

void Player::setMouseClickPos(sf::Vector2f newClick) {
    sounds.at(8).play();
    if(arm){
        if(abs(shape.getSize().x) <= 20.0f){
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