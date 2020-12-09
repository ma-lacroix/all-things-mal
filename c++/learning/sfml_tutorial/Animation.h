// Animation class header file

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <SFML/Graphics.hpp>
#include <iostream>

class Animation {

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;

public:
    Animation(sf::Texture* texture,sf::Vector2u imageCount, float switchTime);
    ~Animation();

    void Update(int row, float deltaTime, bool faceRight);

public:
    sf::IntRect uvRect;
};

Animation::Animation(sf::Texture* texture,sf::Vector2u imageCount, float switchTime){
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;
    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation(){
    std::cout << "Animation destructor called" << std::endl;
}

void Animation::Update(int row, float deltatime, bool faceRight){
    currentImage.y = row;
    totalTime += deltatime;

    if(totalTime >= switchTime){
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x){
            currentImage.x = 0;
        }
    }

    uvRect.top = currentImage.y * uvRect.height;
    
    if (faceRight){
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else {
        uvRect.left = (currentImage.x+1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

}

#endif