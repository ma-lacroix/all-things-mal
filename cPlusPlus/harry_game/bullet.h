// Bullet class

#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "collider.h"

class Bullet {

private:
    sf::RectangleShape some_shape;
    sf::Vector2f movement_speed;

public:
    Bullet(sf::Vector2f position, sf::Vector2f movement_speed);
    ~Bullet();
    void Update(float deltatime);
    void Stop();
    void Draw(sf::RenderWindow& window);
    int getSpeed() {return movement_speed.x;};
    Collider GetCollider() { return Collider(some_shape);};
    float getPosition() {return some_shape.getPosition().x;};
    void makeTransparent();
};

Bullet::Bullet(sf::Vector2f position, sf::Vector2f movement_speed){
    some_shape.setSize({15.0f,7.0f});
    some_shape.setPosition(position);
    some_shape.setFillColor(sf::Color::White);
    this->movement_speed = movement_speed;
}

Bullet::~Bullet(){
    printf("Bullet destructor called");
}

void Bullet::Update(float deltatime){
    some_shape.move(movement_speed*deltatime);
}

void Bullet::Stop(){
    some_shape.move({0,0});
    movement_speed.x = 0;
}

void Bullet::makeTransparent(){
    some_shape.setFillColor(sf::Color(255,255,255,0));
}

void Bullet::Draw(sf::RenderWindow& window){
    window.draw(some_shape);
}



#endif