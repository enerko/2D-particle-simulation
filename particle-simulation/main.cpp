#include <iostream>
#include <SFML/Graphics.hpp>
#include "particle_manager.hpp"
#include "constants.hpp"
#include <sstream>
#include <fstream>
#include <direct.h> // _getcwd
#define GetCurrentDir _getcwd



int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "2D Particle Simulation");
    ParticleManager particleManager;

    sf::Clock clock;

    char currentPath[FILENAME_MAX];
    if (GetCurrentDir(currentPath, sizeof(currentPath)))
    {
        std::cout << "Current Working Directory: " << currentPath << std::endl;
    }

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cout << "Font not found!" << std::endl;
    }

    sf::Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(20);
    displayText.setFillColor(sf::Color::White);
    displayText.setPosition(SCREEN_MARGIN, SCREEN_MARGIN);

    // Game loop
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        if (particleManager.getNumParticles() < 1000) particleManager.spawnParticle(sf::Vector2f(50, 50), sf::Vector2f(1, 1));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Text display
        std::ostringstream ss;
        ss << "Particles: " << particleManager.getNumParticles() << "\n"
            << "FPS: " << static_cast<int>(1/deltaTime);
        displayText.setString(ss.str());

        // Update particles
        particleManager.updateParticles(deltaTime);

        // Render text and particles
        window.clear();
        particleManager.render(window);
        window.draw(displayText);
        window.display();
    }

    return 0;
}