// class handling the onscreen ennemies

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "collider.h"
#include "object.h"

class Enemy: public Object {
private:
    bool lookRight;
    int healtPoints;
    float switchTime;
    float totalTime;
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

public:
    Enemy(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, 
            bool clipping, int healtPoints, sf::Vector2u imageCount, float switchTime);
    ~Enemy();
    void Update(float deltatime);
    void Update_Animation(float deltatime, int row);
    
    sf::RectangleShape main_enemy;
    sf::Vector2f getPosition() {return main_enemy.getPosition();};
    sf::IntRect textureSize;
};

Enemy::Enemy(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, 
                bool clipping, int healtPoints, sf::Vector2u imageCount, float switchTime)
        : Object(textureFile,objectSize,position,clipping){
    this->healtPoints = healtPoints;
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    currentImage = {0,0};
    textureSize.width = textureFile->getSize().x/imageCount.x;
    textureSize.height = textureFile->getSize().y/imageCount.y;
    std::cout << "x: " << textureSize.width << " y: " << textureSize.height << std::endl; 
    main_enemy.setSize(sf::Vector2f(objectSize));
    // main_sprite.setOrigin(main_sprite.getSize() / 2.0f);
    main_enemy.setPosition(position);
    main_enemy.setTexture(textureFile);
}

Enemy::~Enemy(){
}

void Enemy::Update(float deltaTime){
// updates the sprite's position on screen  

    printf("CurrentX: %i, CurrentY: %i\n",currentImage.x,currentImage.y);
    Update_Animation(deltaTime,0);
    
}

void Enemy::Update_Animation(float deltaTime, int row){
// updates the sprite animation based on the clock time
    currentImage.y = row;
    totalTime += deltaTime;
    if(totalTime >= switchTime){
        currentImage.x++;
        totalTime -= switchTime;
        // to match the sprite map
        if(currentImage.x >= imageCount.x){
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
     main_enemy.setTextureRect(textureSize);
}

#endif

