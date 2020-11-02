// object class

#ifndef _SUN_H_
#define _SUN_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
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
    void Movement(float,float);
    bool Collision(sf::Vector2f);
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
    shape.setRotation(angle);
}

void Sun::Movement(float deltatime,float Ycoord){
    std::srand(time(0));
    float randFactor = rand()%2-1; // number between -1 and 1
    if(shape.getPosition().y-Ycoord > 600.0f){
        shape.move(400.0f*randFactor,-1500.0f);
    }else{
        Rotate();
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

bool Sun::Collision(sf::Vector2f plrPos){
    if(abs(shape.getPosition().x - plrPos.x) < 130.0f &
       abs(shape.getPosition().y - plrPos.y) < 130.0f){
            shape.setFillColor(sf::Color(255.0f,50.0f,50.0f,255.0f));
            return true;
       }else{
            shape.setFillColor(sf::Color(255.0f,255.0f,255.0f,255.0f));
            return false;
       }
}

void Sun::Stop(){
    // shape.setFillColor(sf::Color::Blue);
}

void Sun::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif