// player class header file

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"

class Player {

private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;

public:
    // Player();
    Player(sf::Texture* texture,sf::Vector2u imageCount, float switchTime,float speed);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() {return body.getPosition();};
};

Player::Player(sf::Texture* texture,sf::Vector2u imageCount, float switchTime,float speed):
    animation(texture,imageCount,switchTime) {
        this->speed = speed;
        row = 0;
        faceRight = true;
        body.setSize(sf::Vector2f(100.0f, 150.0f));
        body.setOrigin(body.getSize() / 2.0f);
        body.setPosition(206.0f, 206.0f);
        body.setTexture(texture);
    }

Player::~Player(){
    std::cout << "Destructor called" << std::endl;
};

void Player::Update(float deltaTime){
    sf::Vector2f movement(0.0f,0.0f);

    // keystrokes
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        movement.x -= speed*deltaTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        movement.x += speed*deltaTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        movement.y -= speed*deltaTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        movement.y += speed*deltaTime;
    }

    // animation
    if (movement.y != 0.0f){
        row = 1;
    }
    else if (movement.x == 0.0f){
        row = 0;
    }
    else{
        row = 1;
        if (movement.x > 0.0f) {
            faceRight = true;
        }
        else {
            faceRight = false;
        }
    }
    animation.Update(row,deltaTime,faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
    
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(body);
}