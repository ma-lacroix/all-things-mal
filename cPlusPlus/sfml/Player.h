// player class header file

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Collider.h"

class Player {

private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
    sf::Vector2f velocity;
    bool canJump {true};
    float jumpHeight;

public:
    // Player();
    Player(sf::Texture* texture,sf::Vector2u imageCount, float switchTime,float speed, 
                        float jumpHeight);
    ~Player();
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() {return body.getPosition();};
    Collider GetCollider() { return Collider(body);};
    void OnCollision(sf::Vector2f direction);
};

Player::Player(sf::Texture* texture,sf::Vector2u imageCount, float switchTime,float speed,
                        float jumpHeight):
    animation(texture,imageCount,switchTime) {
        this->speed = speed;
        this->jumpHeight = jumpHeight;
        row = 0;
        faceRight = true;
        body.setSize(sf::Vector2f(100.0f, 150.0f));
        body.setOrigin(body.getSize() / 2.0f);
        body.setPosition(206.0f, 206.0f);
        body.setTexture(texture);
    }

Player::~Player(){
    std::cout << "Player destructor called" << std::endl;
};

void Player::Update(float deltaTime){

    velocity.x = 0.0f;
    float gravity {981.0f};

    // keystrokes
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        velocity.x -= speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        velocity.x += speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && canJump){
        canJump = false;
        velocity.y = -sqrtf(2.0f * gravity * jumpHeight);
    }

    velocity.y += gravity * deltaTime;

    // animation
    if (velocity.x == 0.0f){
        row = 0;
    }
    else{
        row = 1;
        if (velocity.x > 0.0f) {
            faceRight = true;
        }
        else {
            faceRight = false;
        }
    }
    animation.Update(row,deltaTime,faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(velocity * deltaTime);
    
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction){

    //collision on the left
    if (direction.x < 0.0f){
        velocity.x = 0.0f;
    }
    //collision on the right
    else if (direction.x > 0.0f){
        velocity.x = 0.0f;
    }
    //collision on the bottom
    if (direction.y < 0.0f){
        velocity.y = 0.0f;
        canJump = true;
    }
    //collision on the top
    else if (direction.y > 0.0f){
        velocity.y = 0.0f;
    }

}

#endif