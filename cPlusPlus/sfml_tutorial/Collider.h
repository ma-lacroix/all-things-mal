// Collision detection class

#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Collider {

private:
    sf::RectangleShape& body;

public:
    Collider(sf::RectangleShape &body);
    ~Collider();

    bool CheckCollision(Collider other, sf::Vector2f& direction, float rebound);

public:
    void Move(float dx, float dy) {body.move(dx,dy);};
    sf::Vector2f GetPosition() {return body.getPosition();};
    sf::Vector2f GetHalfSize() {return body.getSize() / 2.0f;};

};

Collider::Collider(sf::RectangleShape& body):
    body(body) {}

Collider::~Collider() {
    // std::cout << "Collider destructor called" << std::endl;
}

bool Collider::CheckCollision(Collider other, sf::Vector2f& direction, float rebound){

    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    
    float deltax = otherPosition.x - thisPosition.x;
    float deltay = otherPosition.y - thisPosition.y;
    float intersectX = fabs(deltax) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = fabs(deltay) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f){
        rebound = std::min(std::max(rebound, 0.0f),1.0f);

        if(intersectX > intersectY) {
            if (deltax > 0.0f){
                Move(intersectX*(1.0f-rebound),0.0f);
                other.Move(-intersectX * rebound, 0.0f);
                direction.x = 1.0f;
                direction.y = 0.0f;
            }
            else
            {
                Move(-intersectX*(1.0f-rebound),0.0f);
                other.Move(intersectX * rebound, 0.0f);
                direction.x = -1.0f;
                direction.y = 0.0f;
            }
            
        }
        else {
            if (deltay > 0.0f){
                Move(0.0f,intersectY*(1.0f-rebound));
                other.Move(0.0f,-intersectY * rebound);
                direction.x = 0.0f;
                direction.y = 1.0f;
            }
            else
            {
                Move(0.0f,-intersectY*(1.0f-rebound));
                other.Move(0.0f,intersectY * rebound);
                direction.x = 0.0f;
                direction.y = -1.0f;
            }
            
        }

        return true;
    }

    return false;

}

#endif