// class handling the player and its movements

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
private:
    float speed;
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    sf::Vector2u velocity;
    float switchTime;
    float totalTime;
    bool lookRight;

public:
    Player(sf::Texture* textureFile,float speed,float switchtime,sf::Vector2u imageCount);
    ~Player();
    sf::RectangleShape main_sprite;
    void Update(float deltaTime);
    void Update_Animation(float deltaTime);
    void Draw(sf::RenderWindow&);
    sf::IntRect textureSize;
};

Player::Player(sf::Texture* textureFile,float speed,float switchTime,sf::Vector2u imageCount) 
    // : Animation() // when animations are enabled
    {
    this->speed = speed;
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
    Update_Animation(deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        main_sprite.move(-speed,0.0f);
        lookRight = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        main_sprite.move(speed,0.0f);
        lookRight = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        main_sprite.move(0.0f,speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        main_sprite.move(0.0f,-speed);
    }
}

void Player::Update_Animation(float deltaTime){
// updates the sprite animation based on the clock time
    currentImage.y = 0;
    totalTime += deltaTime;
    if(totalTime >= switchTime){
        currentImage.x++;
        totalTime -= switchTime;
        if (currentImage.x >= imageCount.x){
            currentImage.x = 0;
        }
    }
    textureSize.top = currentImage.y * textureSize.height;
    
    if (lookRight){
        // textureSize.left = currentImage.x * textureSize.width;
        // textureSize.width = abs(textureSize.width);
        main_sprite.setScale(1.0f,1.0f);
    }
    else{
        // textureSize.left = (currentImage.x+1) * textureSize.width;
        // textureSize.width = -(textureSize.width);
        main_sprite.setScale(-1.0f,1.0f);
    }
    main_sprite.setTextureRect(textureSize);
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(main_sprite);
}