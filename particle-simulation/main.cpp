#include <iostream>
#include <SFML/Graphics.hpp>
#include "particle_manager.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "2D Particle Simulation");
    ParticleManager particleManager;

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    particleManager.spawnParticles(mousePosition);
                }
            }

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Update particles
        particleManager.updateParticles(deltaTime);

        // Render particles
        window.clear();
        particleManager.render(window);
        window.display();
    }

    return 0;
}