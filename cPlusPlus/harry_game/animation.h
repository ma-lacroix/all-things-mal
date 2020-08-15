// class handling the sprite animations

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Animation{
private:
    sf::Texture* someTexture;
    sf::Vector2u imageCount;
    float switchTime;
    int row_number;

    
public:
    Animation(sf::Texture*,sf::Vector2u, float,int);
    ~Animation();
    sf::Vector2u textureSize;
};

Animation::Animation(sf::Texture* someTexture,sf::Vector2u imageCount, float switchTime,int row_number)
    : {}

Animation::~Animation(){}
#endif