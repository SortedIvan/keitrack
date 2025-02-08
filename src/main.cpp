#include <iostream>
#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(1000, 800),
        "2D-Raycasting");

    sf::Event e;


    // Main loop
    while (window.isOpen())
    {
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            if (e.type == sf::Event::KeyReleased)
            {
                if (e.key.code == sf::Keyboard::LShift)
                {

                }
            }

            // Run updates
           
            // Clear the window
            window.clear(sf::Color::Black);

            // draw

            // display
            window.display();
        }
    }
}