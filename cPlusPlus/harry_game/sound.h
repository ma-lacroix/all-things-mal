// default level boundaries

#ifndef _SOUND_H_
#define _SOUND_H_

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

class Sound {
private:
    sf::Sound sound;
public:
    Sound(std::string soundFile);
    ~Sound();
    sf::Sound load_sound();
};

Sound::Sound(std::string soundFile){
    this->sound = load_sound();
}

sf::Sound load_sound(std::string soundFile){
    sf::SoundBuffer buffer;
    sf::Sound sound;
    
    if (!buffer.loadFromFile(soundFile)){
        printf("Sound not loaded correctly");
    }
    sound.setBuffer(buffer);
    
    return sound;
}

#endif