// object class

#ifndef _SUN_H_
#define _SUN_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "object.h"
#define PI 3.14159265

class Sun: public Object {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f mainPlayerPos;
    sf::Vector2f objectSize;
    float speed;
    float angle;
    bool clickToRight;
    char playstate;
public:
    Sun(sf::Texture* textureFile, sf::Vector2f,sf::Vector2f,float);
    ~Sun();
    void State(float);
    void ifToRight();
    void Rotate();
    void Movement(float,float,sf::Vector2f);
    void Stop();
    void setPlayerPos(sf::Vector2f Pos) {mainPlayerPos = Pos;};
    void Draw(sf::RenderWindow&);
    sf::Vector2f getPosition() {return shape.getPosition();};
};

Sun::Sun(sf::Texture* textureFile, sf::Vector2f objectSize, sf::Vector2f position, float speed)
    :Object(textureFile, objectSize,position){
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setOrigin(objectSize.x/2,objectSize.y/2);
    this->objectSize = objectSize;
    this->speed = speed;
    velocity = {0.0f,0.0f};
    mainPlayerPos = {0.0f,0.0f};
    clickToRight = false;
    shape.setTexture(textureFile);
}

Sun::~Sun(){
}

void Sun::ifToRight(){    
    if(mainPlayerPos.x>shape.getPosition().x){
        clickToRight = true;
    }else{
        clickToRight = false;
    }
}

void Sun::Rotate(){
    // Pythagoras theorem to determine angle of shape using trigonometry
    float a = mainPlayerPos.y-shape.getPosition().y;
    float b = mainPlayerPos.x-shape.getPosition().x;
    angle = atanf(a/b)*180/PI;
    // if(clickToRight){
    //     angle+=180;
    // }
    shape.setRotation(angle);
}

void Sun::Movement(float deltatime,float Ycoord,sf::Vector2f branch1Pos){
    if(shape.getPosition().y-Ycoord > 600.0f){
        shape.move(0.0f,-1500.0f);
    }else{
        sf::Vector2f direction;
        sf::Vector2f direction_norm;
        direction.x = mainPlayerPos.x-(shape.getPosition().x);
        direction.y = mainPlayerPos.y-(shape.getPosition().y);
        direction_norm = direction / sqrtf(direction.x * direction.x + direction.y * direction.y); // avoid speed changes
        velocity = direction_norm*deltatime*speed;
        if(abs(direction.x+direction.y)>0.7f){
            shape.move(velocity);
        }else{
            mainPlayerPos = {0.0f,0.0f};
            velocity = {0.0f,0.0f};
        }
    }
}

void Sun::Stop(){
    // shape.setFillColor(sf::Color::Blue);
}

void Sun::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif