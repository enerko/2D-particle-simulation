#pragma once

#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "constants.hpp"

class ParticleManager
{
public: 
	ParticleManager();
	~ParticleManager();

	void spawnParticle(sf::Vector2f position, sf::Vector2f velocity);
	void updateParticles(float deltaTime);
	void render(sf::RenderWindow& renderer);
	void checkCollision(float deltaTime);

	int getNumParticles() { return particles.size();  }

private:
	std::vector<Particle> particles;
	const sf::Vector2f gravity = { 0.0f, 30.0f };

	bool isColliding(const Particle& p1, const Particle& p2);
	void resolveCollision(Particle& p1, Particle& p2);
};