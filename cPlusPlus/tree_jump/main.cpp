/*
#######################################

    A point and click tree hopping game using SFML
    Author: Marc-Antoine Lacroix

#######################################
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "app.h"

int main() {

    // initialising game window & view

    sf::Music main_song;
    main_song.openFromFile("a_assets/main_song.flac");

    app app;
    float SCREEN_WIDTH {1600.0f};
    float SCREEN_HEIGHT {1200.0f};
    static const float VIEW_HEIGHT = SCREEN_HEIGHT;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Tree jump",sf::Style::Close | sf::Style::Resize);
    sf::View mainmenu(sf::Vector2f(0.0f,0.0f),sf::Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH));
    sf::View frontview(sf::Vector2f(0.0f,0.0f),sf::Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH));
    sf::View HUD(sf::Vector2f(0.0f,0.0f),sf::Vector2f(SCREEN_HEIGHT,SCREEN_WIDTH));

    app.game(main_song,window,mainmenu,frontview,HUD,VIEW_HEIGHT);

    return 0;
}