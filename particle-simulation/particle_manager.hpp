#pragma once

#include <SFML/Graphics.hpp>
#include "particle.hpp"

class ParticleManager
{
public: 
	ParticleManager();
	~ParticleManager();

	void spawnParticles(sf::Vector2f position);
	void updateParticles(float deltaTime);
	void render(sf::RenderWindow& renderer);
private:
	std::vector<Particle> particles;
	sf::Vector2f gravity = { 0.0f, 9.91f };
};