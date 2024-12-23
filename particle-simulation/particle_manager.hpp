#pragma once

#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "constants.hpp"

class ParticleManager
{
public: 
	ParticleManager();
	~ParticleManager();

	void spawnParticles(sf::Vector2f position);
	void updateParticles(float deltaTime);
	void render(sf::RenderWindow& renderer);
	void checkCollision(float deltaTime);

private:
	std::vector<Particle> particles;
	sf::Vector2f gravity = { 0.0f, 20.0f };

	bool isColliding(const Particle& p1, const Particle& p2);
	void resolveCollision(Particle& p1, Particle& p2);
};