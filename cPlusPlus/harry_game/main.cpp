/*
########################

    A jump and run game using the SFML C++ library.
    Author: Marc-Antoine Lacroix

    All images, sounds and sprite maps: opengameart.org 
    Music: Clement Panchout
    http://www.clementpanchout.com/

    Special thanks to Hilze Vonck and his SFML tutorial. He's awesome.
    https://www.youtube.com/watch?v=axIgxBQVBg0

########################
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "main_app.h"

int main() {
    
    sf::Music main_song;
    main_song.openFromFile("assets/ClementPanchout_Sweet70s.wav");

    // initialising game window & view

    main_app app;
    float SCREEN_WIDTH {800.0};
    float SCREEN_HEIGHT {800.0};
    static const float VIEW_HEIGHT = SCREEN_HEIGHT;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Hipster Harry",sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH));
    sf::View HUD(sf::Vector2f(0.0f,0.0f),sf::Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH));

    app.game(main_song,window,view,HUD,VIEW_HEIGHT);
    // game(main_song,window,view,HUD,VIEW_HEIGHT);

    return 0;
}