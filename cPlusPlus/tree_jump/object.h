// object class

#ifndef _OBJECT_H_
#define _OBJECT_H_
#define PI 3.14159265

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Object {
private:
    sf::RectangleShape shape;
    float MouseClickY;
public:
    Object(sf::Texture*, sf::Vector2f, sf::Vector2f);
    ~Object();
    sf::Vector2f getPosition() {return shape.getPosition();};
    void setMouseClickY(float newY) {MouseClickY = newY;};
    void setNoLine(){shape.setOutlineColor(sf::Color::Transparent);};
    void setTransparency(int num){shape.setFillColor(sf::Color(255,255,255,num));};
    void setRotation(float degrees){shape.rotate(degrees);};
    void moveCenter(sf::Vector2f);
    void Animate(float,bool);
    void Movement(float);
    void Draw(sf::RenderWindow&);
};

Object::Object(sf::Texture* textureFile, sf::Vector2f objectSize, sf::Vector2f position){
    // shape.setOrigin(objectSize.x/2,objectSize.y/2);
    shape.setPosition(position);
    shape.setSize(objectSize);
    shape.setFillColor(sf::Color(255,255,255,255));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(8.0f);
    shape.setTexture(textureFile);
    MouseClickY = 5000.0f;
}

Object::~Object(){
}

void Object::moveCenter(sf::Vector2f newPos){
    shape.setOrigin(shape.getSize()/2.0f);
    shape.setPosition(newPos);
}

void Object::Animate(float totaltime, bool horiz){
    float velocity;
    velocity = std::sinf(totaltime*PI)/10.0f;
    if(horiz){
        shape.move(-velocity,0.0f);
    }else{
        shape.move(0.0f,velocity);
    }
}

void Object::Movement(float deltatime){
    sf::Vector2f direction;
    sf::Vector2f direction_norm;
    sf::Vector2f velocity;
    direction.x = 0.0f;
    direction.y = MouseClickY-(shape.getPosition().y);
    direction_norm = direction / sqrtf(direction.x * direction.x + direction.y * direction.y); // avoid speed changes
    velocity = direction*deltatime*0.8f;
    if(abs(direction.x+direction.y)>0.7f){
        shape.move(velocity);
    }
}

void Object::Draw(sf::RenderWindow& window){
    window.draw(shape);
}

#endif