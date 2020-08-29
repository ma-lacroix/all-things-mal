// class handling the player and its movements

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include "collider.h"
#include "level.h"
#include <iostream>
#include <math.h>

class Player {
private:
    Level level;
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    sf::Vector2f velocity;
    bool lookRight;
    float switchTime;
    float totalTime;
    float speed;
    float jumpHeight;
    unsigned int row;
    float gravity;
    bool canJump;

public:
    Player(sf::Texture* textureFile,float speed,float switchtime,float jumpHeight,
                sf::Vector2u imageCount);
    ~Player();
    void Update(float deltaTime);
    void Update_Animation(float deltaTime, int row);
    void Draw(sf::RenderWindow&);
    void OnCollision(sf::Vector2f direction);
    Collider GetCollider() { return Collider(main_sprite);};
    
    sf::RectangleShape main_sprite;
    sf::Vector2f getPosition() {return main_sprite.getPosition();};
    sf::IntRect textureSize;
};

Player::Player(sf::Texture* textureFile,float speed,float switchTime,float jumpHeight,
                sf::Vector2u imageCount) 
    // : Animation() // when animations are enabled
    {
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    this->switchTime = switchTime;
    this->imageCount = imageCount; 
    lookRight = true;
    totalTime = 0.0f;
    currentImage = {0,0};
    gravity = 981.0f;
    canJump = true;
    textureSize.width = textureFile->getSize().x/imageCount.x;
    textureSize.height = textureFile->getSize().y/imageCount.y;
    std::cout << "x: " << textureSize.width << " y: " << textureSize.height << std::endl; 
    main_sprite.setSize(sf::Vector2f(100.0f, 100.0f));
    // main_sprite.setOrigin(main_sprite.getSize() / 2.0f);
    main_sprite.setPosition(200.0f,200.0f);
    main_sprite.setTexture(textureFile);
    main_sprite.setOutlineThickness(1);
}

Player::~Player(){
    std::cout << "Player destructor called" << std::endl;
};

void Player::Update(float deltaTime){
// updates the sprite's position on screen  
    // printf("PosX: %f, PosY: %f\n",main_sprite.getPosition().x,main_sprite.getPosition().y);
    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && main_sprite.getPosition().x > level.getLeft_b()){
    // go left
        velocity.x -= speed;
        lookRight = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && main_sprite.getPosition().x < level.getRight_b()){
    // go right
        velocity.x += speed;
        lookRight = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && canJump){
    // jump
        velocity.y = -sqrtf(gravity * jumpHeight);
        canJump = false;
    }
    
    velocity.y += (gravity * deltaTime);

    if (velocity.x == 0.0f && canJump == true){
        row = 0;
    }else if(velocity.x!=0.0f && canJump == true){
        row=1;
    }else{
        row=3;
    }

    Update_Animation(deltaTime, row);
    main_sprite.move(velocity*deltaTime);
}

void Player::Update_Animation(float deltaTime, int row){
// updates the sprite animation based on the clock time
    currentImage.y = row;
    totalTime += deltaTime;
    if(totalTime >= switchTime){
        currentImage.x++;
        totalTime -= switchTime;
        // to match the sprite map
        if(row==0 && currentImage.x >= imageCount.x){
            currentImage.x = 0;
        }else if(row==1 && currentImage.x >=6){
            currentImage.x = 0;
        }else if(row==3 && currentImage.x >=3){
            currentImage.x = 0;
        }
    }
    textureSize.top = currentImage.y * textureSize.height;
    
    if (lookRight){
        textureSize.left = currentImage.x * abs(textureSize.width);
        textureSize.width = abs(textureSize.width);
    }
    else{
        textureSize.left = (currentImage.x+1) * abs(textureSize.width);
        textureSize.width = -abs(textureSize.width);
    }
     main_sprite.setTextureRect(textureSize);
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(main_sprite);
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