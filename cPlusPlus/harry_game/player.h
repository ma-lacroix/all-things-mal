// class handling the player and its movements

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
private:
    float speed;
    sf::Vector2u imageCount;
    float switchTime;
    float totalTime;
    int row_num;
public:
    Player(sf::Texture* textureFile,float speed,float switchtime,sf::Vector2u imageCount);
    ~Player();
    sf::RectangleShape main_sprite;
    void Update(float deltaTime);
    void Draw(sf::RenderWindow&);
    sf::IntRect textureSize;
};

Player::Player(sf::Texture* textureFile,float speed,float switchTime,sf::Vector2u imageCount) 
    // : Animation() // when animations are enabled
    {
    this->speed = speed;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    row_num = 0;
    textureSize.width = textureFile->getSize().x/imageCount.x;
    textureSize.height = textureFile->getSize().y/imageCount.y;
    std::cout << "x: " << textureSize.width << "y: " << textureSize.height << std::endl; 
    main_sprite.setSize(sf::Vector2f(100.0f, 100.0f));
    // main_sprite.setOrigin(main_sprite.getSize() / 2.0f);
    main_sprite.setPosition(206.0f,206.0f);
    main_sprite.setTexture(textureFile);
}

Player::~Player(){
    std::cout << "Player destructor called" << std::endl;
};

void Player::Update(float deltaTime){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        main_sprite.move(-0.1f,0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        main_sprite.move(0.1f,0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        main_sprite.move(0.0f,0.1f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        main_sprite.move(0.0f,-0.1f);
    }
    totalTime += deltaTime;
        if(totalTime >= switchTime){
            totalTime -= switchTime;
            row_num++;

            if (row_num >= imageCount.x){
                row_num = 0;
            }
        }
    main_sprite.setTextureRect(sf::IntRect(textureSize.width*row_num,textureSize.height*0,textureSize.width,textureSize.height));
}

void Player::Draw(sf::RenderWindow& window){
    window.draw(main_sprite);
}