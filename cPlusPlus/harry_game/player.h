// class handling the player and its movements

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Player {
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    sf::Vector2f velocity;
    bool lookRight;
    float switchTime;
    float totalTime;
    float speed;
    float jumpHeight;
    unsigned int row;

public:
    Player(sf::Texture* textureFile,float speed,float switchtime,float jumpHeight,
                sf::Vector2u imageCount);
    ~Player();
    sf::RectangleShape main_sprite;
    void Update(float deltaTime);
    void Update_Animation(float deltaTime, int row);
    void Draw(sf::RenderWindow&);
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
    textureSize.width = textureFile->getSize().x/imageCount.x;
    textureSize.height = textureFile->getSize().y/imageCount.y;
    std::cout << "x: " << textureSize.width << " y: " << textureSize.height << std::endl; 
    main_sprite.setSize(sf::Vector2f(100.0f, 100.0f));
    // main_sprite.setOrigin(main_sprite.getSize() / 2.0f);
    main_sprite.setPosition(206.0f,206.0f);
    main_sprite.setTexture(textureFile);
}

Player::~Player(){
    std::cout << "Player destructor called" << std::endl;
};

void Player::Update(float deltaTime){
// updates the sprite's position on screen  

    // game board coordinates
    float floor {350.0f};
    float left_b {100.0f};
    float right_b {10000.0f};

    // jump data points
    float gravity {981.0f};
    bool canJump {true};
    velocity.x = 0.0f;

    // temporary floor for the sprite to walk on
    if(main_sprite.getPosition().y < floor){
        canJump = false;
        velocity.y += (gravity * deltaTime);
    }else{
        canJump = true;
        velocity.y = 0.0f;
    }
    // temporary game boundaries

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && main_sprite.getPosition().x > left_b){
    // go left
        velocity.x -= speed;
        lookRight = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && main_sprite.getPosition().x < right_b){
    // go right
        velocity.x += speed;
        lookRight = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && canJump){
    // jump
        velocity.y = -sqrtf(gravity * jumpHeight);
        canJump = false;
    }

    if(velocity.x==0.0f && velocity.y==0.0f){
        row=0;
    }else if(velocity.x!=0.0f && velocity.y==0.0f){
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