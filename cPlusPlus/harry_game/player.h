// class handling the player and its movements

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include "collider.h"
#include "level.h"
#include "bullet.h"
#include "object.h"
#include "enemy.h"

class Player {
private:
    Level level;
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    sf::Vector2f velocity;
    bool lookRight;
    bool hit;
    float switchTime;
    float totalTime;
    float speed;
    float jumpHeight;
    unsigned int row;
    unsigned int healthPoints;
    unsigned int shootrefresh;
    float gravity;
    bool canJump;
    std::vector<Bullet*> bullets;

public:
    Player(sf::Texture* textureFile,float speed,float switchtime,float jumpHeight,
                sf::Vector2u imageCount, int shootrefresh);
    ~Player();
    void Update(float deltaTime, int &shootTimer, std::vector<Object> &objects, Enemy &enemy);
    void Update(float deltaTime, int &shootTimer, std::vector<Object> &objects);
    void Update_Animation(float deltaTime, int row);
    void Draw(sf::RenderWindow&);
    void OnCollision(sf::Vector2f direction);
    void ShootBullet(int &shootTimer);
    void ManageBullets(float deltaTime,int MaxBullets,std::vector<Object> &objects, Enemy &enemy);
    void updateHealthPoints(int loss);
    void activateHit() {hit = true;};
    void deactivateHit() {hit = false;};
    void takingHit();
    std::vector<Bullet*> getBullets() {return bullets;};
    Collider GetCollider() { return Collider(main_sprite);};
    int GetHealthPoints() {return healthPoints;};
    
    sf::RectangleShape main_sprite;
    sf::Vector2f getPosition() {return main_sprite.getPosition();};
    sf::IntRect textureSize;
};

Player::Player(sf::Texture* textureFile,float speed,float switchTime,float jumpHeight,
                sf::Vector2u imageCount, int shootrefresh) 
    // : Animation() // when animations are enabled
    {
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    this->switchTime = switchTime;
    this->imageCount = imageCount; 
    this->shootrefresh = shootrefresh;
    lookRight = true;
    totalTime = 0.0f;
    currentImage = {0,0};
    gravity = 981.0f;
    canJump = true;
    healthPoints = 4;
    hit = false;
    textureSize.width = textureFile->getSize().x/imageCount.x;
    textureSize.height = textureFile->getSize().y/imageCount.y;
    std::cout << "x: " << textureSize.width << " y: " << textureSize.height << std::endl; 
    main_sprite.setSize(sf::Vector2f(100.0f, 100.0f));
    // main_sprite.setOrigin(main_sprite.getSize() / 2.0f);
    main_sprite.setPosition(200.0f,200.0f);
    main_sprite.setTexture(textureFile);
    // main_sprite.setOutlineThickness(1);
}

Player::~Player(){
    std::cout << "Player destructor called" << std::endl;
}

void Player::ShootBullet(int &shootTimer){
    canJump = false;
    shootTimer = 0;
    sf::Vector2f bulletpos;
    float bspeed;
    bulletpos = main_sprite.getPosition()+main_sprite.getSize()/2.0f;
    if(lookRight){
        bspeed = 1000.0f;
    }else{
        bspeed = -1000.0f;
    }
    bullets.push_back(new Bullet(bulletpos,{bspeed,0.0f}));
}

void Player::ManageBullets(float deltaTime, int MaxBullets, std::vector<Object> &objects, Enemy &enemy){
// Handles the bullet movements and memory allocated to bullet objects creation
    if(bullets.size()>0){
        for(auto bullet: bullets){
            bool collided {false};
            bool en {false};
            if(enemy.GetCollider().CheckCollision(bullet->GetCollider()) && enemy.Get_Status()){
                collided = true;
                en = true;
            }else{
                for(auto object: objects){
                    if(object.Clipping()){
                        if (object.GetCollider().CheckCollision(bullet->GetCollider())){
                        collided = true;
                        break;          
                        }
                    }
                }
            }
            
            if(en && collided){
                if(bullet->getSpeed()!=0){
                    enemy.Update_Health();
                    bullet->makeTransparent();
                }
                bullet->Stop();
            }else if(collided){
                bullet->Stop();
            }else{
                bullet->Update(deltaTime);
            }
        }
    } 
    if(bullets.size()>MaxBullets){
        bullets.erase(bullets.begin());
    }
}

void Player::Update(float deltaTime, int &shootTimer, std::vector<Object> &objects, Enemy &enemy){
// updates the sprite's position on screen  

    if(healthPoints<1){
        textureSize.top = 3 * textureSize.height; 
        textureSize.left = 5 * abs(textureSize.width);
        textureSize.width = abs(textureSize.width);
        main_sprite.setFillColor(sf::Color(255,255,255,60));
        main_sprite.setTextureRect(textureSize);
    }else{
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && shootTimer >= shootrefresh){
        // attack
            ShootBullet(shootTimer);
        }

        velocity.y += (gravity * deltaTime);

        if(velocity.x == 0.0f && canJump==true){
            row = 0;
        }else if(velocity.x!=0.0f && canJump==true){
            row=1;
        }else{
            row=3;
        }
        
        ManageBullets(deltaTime,8,objects,enemy);

        if(hit){
            takingHit();    
        }else{
            main_sprite.setFillColor(sf::Color::White);
            Update_Animation(deltaTime,row);
        }
        main_sprite.move(velocity*deltaTime);
        
    }
    
}

void Player::Update(float deltaTime, int &shootTimer, std::vector<Object> &objects){
// function overloaded - updates the sprite's position on screen when no enemies are left in the level
    
    if(bullets.size()>0){
    // gets rid of the last bullets
        bullets.erase(bullets.begin());
    }

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

    if(velocity.x == 0.0f && canJump==true){
        row = 0;
    }else if(velocity.x!=0.0f && canJump==true){
        row=1;
    }else{
        row=3;
    }
    
    Update_Animation(deltaTime,row);
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

void Player::takingHit(){
    
    main_sprite.setFillColor(sf::Color::Red);
    textureSize.top = 3 * textureSize.height; 
    if (lookRight){
        textureSize.left = 3 * abs(textureSize.width);
        textureSize.width = abs(textureSize.width);
        main_sprite.setPosition({main_sprite.getPosition().x-2.0f,
                            main_sprite.getPosition().y});
    }
    else{
        textureSize.left = 4 * abs(textureSize.width);
        textureSize.width = -abs(textureSize.width);
        main_sprite.setPosition({main_sprite.getPosition().x+2.0f,
                            main_sprite.getPosition().y});
    }
    main_sprite.setTextureRect(textureSize);
}

void Player::updateHealthPoints(int loss){
    healthPoints-=loss;
}

#endif