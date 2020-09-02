// Bullet class

#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Bullet {

private:
    sf::CircleShape some_shape;
    sf::Vector2f movement_speed;

public:
    Bullet(float radius, sf::Vector2f position, sf::Vector2f movement_speed);
    ~Bullet();
    float getPosition() {return some_shape.getPosition().x;};
    void Update(float deltatime);
    void Draw(sf::RenderWindow& window);
};

Bullet::Bullet(float radius, sf::Vector2f position, sf::Vector2f movement_speed){
    some_shape.setRadius(radius);
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

void Bullet::Draw(sf::RenderWindow& window){
    window.draw(some_shape);
}



#endif