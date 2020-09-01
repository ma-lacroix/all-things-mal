// Collision detection class

#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Collider {

private:
    sf::RectangleShape& some_shape;

public:
    Collider(sf::RectangleShape& some_shape);
    ~Collider();
    bool CheckCollision(Collider main_sprite, sf::Vector2f& direction, float rebound);
    Collider GetCollider() {return Collider(some_shape);};
    void Move(float dx, float dy) {some_shape.move(dx,dy);};
    sf::Vector2f GetPosition() {return some_shape.getPosition();};
    sf::Vector2f GetSize() {return some_shape.getSize();};

};

Collider::Collider(sf::RectangleShape& some_shape):
    some_shape(some_shape) {}

Collider::~Collider() {
    // std::cout << "Collider destructor called" << std::endl;
}

bool Collider::CheckCollision(Collider main_sprite, sf::Vector2f& direction, float rebound){

    sf::Vector2f main_spritePosition = main_sprite.GetPosition();
    sf::Vector2f main_spriteSize = main_sprite.GetSize()+main_spritePosition;
    sf::Vector2f ObjectPosition = GetPosition();
    sf::Vector2f ObjectSize = GetSize()+ObjectPosition;
    
    float deltax = main_spritePosition.x - ObjectPosition.x;
    float deltay = main_spritePosition.y - ObjectPosition.y;
    float intersectX = fabs(deltax) - (main_sprite.GetSize().x + GetSize().x)/2.0f;
    float intersectY = fabs(deltay) - (main_sprite.GetSize().y + GetSize().y)/2.0f;
    
    // collision at the bottom
    if(main_spriteSize.y > ObjectPosition.y && main_spritePosition.y < ObjectPosition.y){
        if(main_spritePosition.x < ObjectSize.x && 
            main_spriteSize.x > ObjectPosition.x &&
            main_spriteSize.x > ObjectSize.x){
                main_sprite.Move(0.0f,intersectY);
                direction.x = 0.0f;
                direction.y = -1.0f;
                return true;
        }
        if(main_spritePosition.x > ObjectPosition.x && 
            main_spriteSize.x > ObjectPosition.x &&
            main_spriteSize.x < ObjectSize.x){
                main_sprite.Move(0.0f,intersectY);
                direction.x = 0.0f;
                direction.y = -1.0f;
                return true;
        }
        if(main_spritePosition.x < ObjectPosition.x && 
            main_spriteSize.x > ObjectPosition.x &&
            main_spriteSize.x < ObjectSize.x){
                main_sprite.Move(0.0f,intersectY);
                direction.x = 0.0f;
                direction.y = -1.0f;
                return true;
        }
    }
    // collision at the top
    if(main_spritePosition.y < ObjectSize.y && main_spriteSize.y > ObjectSize.y){
        if(main_spritePosition.x < ObjectSize.x && 
        main_spriteSize.x > ObjectPosition.x &&
        main_spriteSize.x > ObjectSize.x){
                main_sprite.Move(0.0f,-intersectY);
                direction.x = 0.0f;
                direction.y = 1.0f;
                return true;
        }
        if(main_spritePosition.x > ObjectPosition.x && 
            main_spriteSize.x > ObjectPosition.x &&
            main_spriteSize.x < ObjectSize.x){
                main_sprite.Move(0.0f,-intersectY);
                direction.x = 0.0f;
                direction.y = 1.0f;
                return true;
        }
        if(main_spritePosition.x < ObjectPosition.x && 
            main_spriteSize.x > ObjectPosition.x &&
            main_spriteSize.x < ObjectSize.x){
                main_sprite.Move(0.0f,-intersectY);
                direction.x = 0.0f;
                direction.y = 1.0f;
                return true;
        }
    }
    
    return false;
}

#endif