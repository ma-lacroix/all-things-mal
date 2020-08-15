// Class holding sprite textures 

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Texture {
private:
    std::string file;

public:
    Texture();
    Texture(std::string file);
    ~Texture();
    sf::Texture texture;
};

Texture::Texture(std::string file){
    this->file=file;
    if(!texture.loadFromFile(file)){
        std::cout << "Couldn't load " << file << std::endl;
    }
}

Texture::~Texture() {};

#endif