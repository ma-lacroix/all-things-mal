// zombie game tutorial
// student: Marc-Antoine Lacroix

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"

int main()
{
    system("pwd");
    // The game will always be in one of four states
    enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
    // Start with the GAME_OVER state
    State state = State::GAME_OVER;

    // Get the screen resolution and create an SFML window
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width/2.0;
    resolution.y = sf::VideoMode::getDesktopMode().height/2.0;
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y),
        "Zombie Arena", sf::Style::Titlebar);

    // Create a an SFML View for the main action
    sf::View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    // Here is our clock for timing everything
    sf::Clock clock;
    // How long has the PLAYING state been active
    sf::Time gameTimeTotal;

    // Where is the sf::Mouse in relation to world coordinates
    sf::Vector2f MouseWorldPosition;
    // Where is the sf::Mouse in relation to screen coordinates
    sf::Vector2i MouseScreenPosition;

    // Create an instance of the Player class
    Player player;

    // The boundaries of the arena
    sf::IntRect arena;

    // The main game loop
    while (window.isOpen())
    {
        /*
        ************
        Handle input
        ************
        */

        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                
            {
                // Pause a game while playing
                if (event.key.code == sf::Keyboard::Return &&
                    state == State::PLAYING)
                {
                    std::cout << "Pausing state" << std::endl;
                    state = State::PAUSED;
                }

                // Restart while paused
                else if (event.key.code == sf::Keyboard::Return &&
                    state == State::PAUSED)
                {
                    state = State::PLAYING;
                    // Reset the clock so there isn't a frame jump
                    clock.restart();
                }

                // Start a new game while in GAME_OVER state
                else if (event.key.code == sf::Keyboard::Return &&
                    state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                }

                if (state == State::PLAYING)
                {
                }

            }
        }// End event polling


        // Handle the player quitting
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        // Handle controls while playing
        if (state == State::PLAYING)
        {
            // Handle the pressing and releasing of the WASD keys
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }

        }// End WASD while playing

        // Handle the levelling up state
        if (state == State::LEVELING_UP)
        {
            // Handle the player levelling up
            if (event.key.code == sf::Keyboard::Num1)
            {
                state = State::PLAYING;
            }

            if (event.key.code == sf::Keyboard::Num2)
            {
                state = State::PLAYING;
            }

            if (event.key.code == sf::Keyboard::Num3)
            {
                state = State::PLAYING;
            }

            if (event.key.code == sf::Keyboard::Num4)
            {
                state = State::PLAYING;
            }

            if (event.key.code == sf::Keyboard::Num5)
            {
                state = State::PLAYING;
            }

            if (event.key.code == sf::Keyboard::Num6)
            {
                state = State::PLAYING;
            }
            
            if (state == State::PLAYING)
            {
                // Prepare thelevel
                // We will modify the next two lines later
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                // We will modify this line of code later
                int tileSize = 50;

                // Spawn the player in the middle of the arena
                player.spawn(arena, resolution, tileSize);
                
                // Reset the clock so there isn't a frame jump
                clock.restart();
            }
        }// End levelling up

        /*
        ****************
        UPDATE THE FRAME
        ****************
        */
        if (state == State::PLAYING){
            // Update the delta time
            sf::Time dt = clock.restart();
            // Update the total game time
            gameTimeTotal += dt;
            // Make a decimal fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();

            // Where is the sf::Mouse pointer
            MouseScreenPosition = sf::Mouse::getPosition();

            // Convert sf::Mouse position to world coordinates of mainView
            MouseWorldPosition = window.mapPixelToCoords(
                sf::Mouse::getPosition(), mainView);

            // Update the player
            player.update(dtAsSeconds, sf::Mouse::getPosition());

            // Make a note of the players new position
            sf::Vector2f playerPosition(player.getCenter());

            // Make the view centre around the player
            mainView.setCenter(player.getCenter());
        }// End updating the scene

        /*
        **************
        Draw the scene
        **************
        */

        if (state == State::PLAYING){
            window.clear();

            // set the mainView to be displayed in the window
            // And draw everything related to it
            window.setView(mainView);

            // Draw the player
            window.draw(player.getSprite());
        }

        if (state == State::LEVELING_UP){
        }

        if (state == State::PAUSED){
        }

        if (state == State::GAME_OVER){
        }

        window.display();

    }// End game loop

    return 0;
}
