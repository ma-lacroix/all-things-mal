// default Health boundaries

#ifndef _HEALTH_H_
#define _HEALTH_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "object.h"

class Health{
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
public:
    Health(sf::Texture* textureFile, sf::Vector2u imageCount);
    ~Health();
    void updateHealth(int loss);
    void Draw(sf::RenderWindow& window);

    sf::RectangleShape healthBar;
    sf::IntRect textureSize;
};

Health::Health(sf::Texture* textureFile, sf::Vector2u imageCount){
    this->imageCount = imageCount;
    currentImage = {0,0};
    textureSize.width = textureFile->getSize().x/imageCount.x;
    textureSize.height = textureFile->getSize().y/imageCount.y;
    healthBar.setSize(sf::Vector2f{200.0f,50.0f});
    healthBar.setPosition(sf::Vector2f{-360.0f,-360.0f});
    healthBar.setTexture(textureFile);
    textureSize.top = 0;
    healthBar.setTextureRect(textureSize);
}
Health::~Health(){};

void Health::Draw(sf::RenderWindow& window){
    window.draw(healthBar);
}

void Health::updateHealth(int loss){
    currentImage.y += loss;
    textureSize.top = currentImage.y * textureSize.height;
    healthBar.setTextureRect(textureSize);
}

#endif