#pragma once

#include <SFML/System/Vector2.hpp>

struct Particle
{
	sf::Vector2f currentPostion = {0.0f, 0.0f};
	sf::Vector2f previousPostion = {0.0f, 0.0f};
	sf::Vector2f acceleration = { 0.0f, 0.0f };

	Particle() = default;

	void updateParticle(float deltaTime)
	{
		// Update position using Verlet Integration
		sf::Vector2f newPosition = currentPostion + (currentPostion - previousPostion)
			+ acceleration * (deltaTime * deltaTime);

		previousPostion = currentPostion;
		currentPostion = newPosition;
		acceleration = sf::Vector2f{ 0.0f, 0.0f };
	}

	void setPosition(sf::Vector2f pos)
	{
		currentPostion = pos;
		previousPostion = pos;
		acceleration = sf::Vector2f{ 0.0f, 0.0f };
	}
};