#pragma once

#include <SFML/System/Vector2.hpp>
#include "constants.hpp"

struct Particle
{
	sf::Vector2f currentPostion = {0.0f, 0.0f};
	sf::Vector2f previousPostion = {0.0f, 0.0f};
	sf::Vector2f acceleration = { 0.0f, 0.0f };
	sf::Color color;

	Particle() = default;

	void updateParticle(float deltaTime)
	{
		// Update position using Verlet Integration
		sf::Vector2f newPosition = currentPostion + (currentPostion - previousPostion)
			+ acceleration * (deltaTime * deltaTime);		

		previousPostion = currentPostion;
		currentPostion = newPosition;
		acceleration = sf::Vector2f{ 0.0f, 0.0f };

		// Limit position to within the screen
		if (currentPostion.x > SCREEN_WIDTH - SCREEN_MARGIN)
			setPosition(sf::Vector2f{SCREEN_WIDTH - SCREEN_MARGIN, currentPostion.y});
		else if (currentPostion.x < SCREEN_MARGIN) 
			setPosition(sf::Vector2f{SCREEN_MARGIN, currentPostion.y});

		if (currentPostion.y > SCREEN_HEIGHT - SCREEN_MARGIN) 
			setPosition(sf::Vector2f{currentPostion.x, SCREEN_HEIGHT - SCREEN_MARGIN});
		else if (currentPostion.y < SCREEN_MARGIN) 
			setPosition(sf::Vector2f{currentPostion.x, SCREEN_MARGIN});
	}

	void setPosition(sf::Vector2f pos)
	{
		currentPostion = pos;
		previousPostion = pos;
		acceleration = sf::Vector2f{ 0.0f, 0.0f };
	}
};