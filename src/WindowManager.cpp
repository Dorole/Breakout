#include "WindowManager.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void WindowManager::run()
{
    while (window.isOpen()) 
    {
        sf::Event event;

        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Additional game logic
        window.clear();

        // Draw objects, UI, etc.
        window.display();
    }
}
