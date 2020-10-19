// object class

#ifndef _SHEET_H_
#define _SHEET_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Sheet {
private:
    sf::RectangleShape note1;
    sf::RectangleShape note2;
    sf::RectangleShape note3;
    sf::RectangleShape note4;
    sf::RectangleShape note5;
    sf::RectangleShape note6;
    sf::RectangleShape note7;
    sf::RectangleShape note8;
    std::vector<sf::RectangleShape&> notes;
    int index;


public:
    Sheet(sf::Texture*, char);
    ~Sheet();
    void Draw(sf::RenderWindow&);
};

Sheet::Sheet(sf::Texture* textureFile, char code){
    notes.push_back(note1);
    notes.push_back(note2);
    notes.push_back(note3);
    notes.push_back(note4);
    notes.push_back(note5);
    notes.push_back(note6);
    notes.push_back(note7);
    notes.push_back(note8);
    switch (code)
    {
    case code == 'A':
        for(auto note: notes){
            note.setPosition({}) // GOT HERE -> create melodies
        }
        break;
    default:
        break;
    }
}

Sheet::~Sheet(){
}

void Sheet::Draw(sf::RenderWindow& window){
    for(auto note: notes){
        window.draw(note);
    }
}

#endif