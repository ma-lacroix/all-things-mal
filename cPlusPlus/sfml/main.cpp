// Testing SFML library

#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    
    int SCREEN_WIDTH {800};
    int SCREEN_HEIGHT {600};
    
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Some game");

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        window.clear();

        //objects to draw

        window.display();
    }

    return EXIT_SUCCESS;
}