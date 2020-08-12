
#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Platform {
private:

    sf::RectangleShape body;

public:
    Platform(sf::Texture* texture,sf::Vector2f size, sf::Vector2f position);
    ~Platform();

    void Draw(sf::RenderWindow& window);
    Collider GetCollider() {return Collider(body);};

};

Platform::Platform(sf::Texture* texture,sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);
    // body.setTextureRect({0, 0, 100, 100});
};

Platform::~Platform() {
    std::cout << "Platform destructor called" << std::endl;    
}

void Platform::Draw(sf::RenderWindow& window){
    window.draw(body);
}

#endif