// class handling the onscreen ennemies

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "collider.h"
#include "player.h"

class Enemy: public Object {
private:
    bool lookRight;
    bool alive;
    int healthPoints;
    float switchTime;
    float totalTime;
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

public:
    Enemy(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, 
            bool clipping, int healthPoints, sf::Vector2u imageCount, float switchTime);
    ~Enemy();
    void Update(float deltatime);
    void Update_Animation(float deltatime, int row);
    void Update_Health();
    void Update_Position(float deltaTime);
    bool Get_Status() {return alive;};
    void Draw(sf::RenderWindow &window);
    sf::RectangleShape main_enemy;
    sf::Vector2f getPosition() {return main_enemy.getPosition();};
    sf::IntRect textureSize;
};

Enemy::Enemy(sf::Texture* textureFile,sf::Vector2f objectSize, sf::Vector2f position, 
                bool clipping, int healthPoints, sf::Vector2u imageCount, float switchTime)
        : Object(textureFile,objectSize,position,clipping){
    this->healthPoints = healthPoints;
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    lookRight = true;
    alive = true;
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
    
    int row;
    if(healthPoints==0){
        alive = false;
    }
    if(healthPoints > 5){
        row = 0;
    }else{
        row = 1;
    }
    
    Update_Position(deltaTime);
    Update_Animation(deltaTime,row);
    
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

void Enemy::Update_Health(){
    --healthPoints;
}

void Enemy::Update_Position(float deltatime){
    sf::Vector2f velocity {-20.0f,0.0f};
    main_enemy.move(deltatime*velocity);
}

void Enemy::Draw(sf::RenderWindow &window){
    window.draw(main_enemy);
}



#endif

