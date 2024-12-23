#pragma once

#include <SFML/System/Vector2.hpp>
#include "constants.hpp"

struct Particle
{
	sf::Vector2f currentPosition = {0.0f, 0.0f};
	sf::Vector2f previousPosition = {0.0f, 0.0f};
	sf::Vector2f acceleration = { 0.0f, 0.0f };
	sf::Color color;

	Particle() = default;

	void updateParticle(float deltaTime)
	{
		// Update position using Verlet Integration
		sf::Vector2f newPosition = currentPosition + (currentPosition - previousPosition)
			+ acceleration * (deltaTime * deltaTime);		

		previousPosition = currentPosition;
		currentPosition = newPosition;
		acceleration = sf::Vector2f{ 0.0f, 0.0f };

		// Limit position to within the screen
		checkBoundaries(deltaTime);
	}

	void setPosition(sf::Vector2f pos)
	{
		currentPosition = pos;
		previousPosition = pos;
		acceleration = sf::Vector2f{ 0.0f, 0.0f };
	}

	void checkBoundaries(float deltaTime)
	{
		float dampingCoeff = 0.9f; // To reduce bouncing over time

		// Bounce by reversing velocity (currentPosition - previousPosition) multiplied by damping
		
		// Right wall
		if (currentPosition.x > SCREEN_WIDTH - SCREEN_MARGIN)
		{
			currentPosition.x = SCREEN_WIDTH - SCREEN_MARGIN;

			// Set previous position to be flipped against the wall as the axis, i.e. pretend as if it came from the left
			previousPosition.x = currentPosition.x + (currentPosition.x - previousPosition.x) * dampingCoeff;
		}

		// Left wall
		else if (currentPosition.x < SCREEN_MARGIN)
		{
			currentPosition.x = SCREEN_MARGIN;
			previousPosition.x = currentPosition.x + (currentPosition.x - previousPosition.x) * dampingCoeff;
		}

		// Bottom wall
		if (currentPosition.y > SCREEN_HEIGHT - SCREEN_MARGIN)
		{
			currentPosition.y = SCREEN_HEIGHT - SCREEN_MARGIN;
			previousPosition.y = currentPosition.y + (currentPosition.y - previousPosition.y) * dampingCoeff;
		}

		// Top wall
		else if (currentPosition.y < SCREEN_MARGIN)
		{
			currentPosition.y = SCREEN_MARGIN;
			previousPosition.y = currentPosition.y + (currentPosition.y - previousPosition.y) * dampingCoeff;
		}

		// Reset acceleration
		acceleration = sf::Vector2f(0.0f, 0.0f);
	}
};