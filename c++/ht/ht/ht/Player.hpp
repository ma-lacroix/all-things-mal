//
//  Player.hpp
//  ht
//
//  Created by Marc-Antoine Lacroix on 20/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    sf::Vector2f m_Position;
    sf::Sprite m_Sprite;
    sf::Texture m_Texture;
    sf::Vector2f m_Resolution;
    sf::IntRect m_Arena;
    int m_TileSize;
    bool m_UpPressed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;
    int m_Health;
    int m_MaxHealth;
    sf::Time m_LastHit;
    float m_Speed;
public:
    Player();
    ~Player();
    void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
    bool hit(sf::Time timeHit);
    sf::Time getLastHitTime();
    sf::FloatRect getPosition();
    sf::Vector2f getCenter();
    float getRotation();
    sf::Sprite getSprite();
    int getHealth();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();
    void update(float elapsedTime, sf::Vector2i mousePosition);
    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);
};

#endif /* Player_hpp */
