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
		checkBoundaries(deltaTime);
	}

	void setPosition(sf::Vector2f pos)
	{
		currentPostion = pos;
		previousPostion = pos;
		acceleration = sf::Vector2f{ 0.0f, 0.0f };
	}

	void checkBoundaries(float deltaTime)
	{
		float dampingCoeff = 0.9f; // To reduce bouncing over time

		// Bounce by reversing velocity (currentPosition - previousPosition) multiplied by damping
		
		// Right wall
		if (currentPostion.x > SCREEN_WIDTH - SCREEN_MARGIN)
		{
			currentPostion.x = SCREEN_WIDTH - SCREEN_MARGIN;

			// Set previous position to be flipped against the wall as the axis, i.e. pretend as if it came from the left
			previousPostion.x = currentPostion.x + (currentPostion.x - previousPostion.x) * dampingCoeff;
		}

		// Left wall
		else if (currentPostion.x < SCREEN_MARGIN)
		{
			currentPostion.x = SCREEN_MARGIN;
			previousPostion.x = currentPostion.x + (currentPostion.x - previousPostion.x) * dampingCoeff;
		}

		// Bottom wall
		if (currentPostion.y > SCREEN_HEIGHT - SCREEN_MARGIN)
		{
			currentPostion.y = SCREEN_HEIGHT - SCREEN_MARGIN;
			previousPostion.y = currentPostion.y + (currentPostion.y - previousPostion.y) * dampingCoeff;
		}

		// Top wall
		else if (currentPostion.y < SCREEN_MARGIN)
		{
			currentPostion.y = SCREEN_MARGIN;
			previousPostion.y = currentPostion.y + (currentPostion.y - previousPostion.y) * dampingCoeff;
		}

		// Reset acceleration
		acceleration = sf::Vector2f(0.0f, 0.0f);
	}
};