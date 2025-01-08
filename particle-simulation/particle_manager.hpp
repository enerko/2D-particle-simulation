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

	void createForce(sf::Vector2f forcePosition, float initialStrength, float falloffDistance, float decayRate);
	void updateForces(float deltaTime);

	struct ForceEffect
	{
		sf::Vector2f position;
		float strength;       // Current strength of the force
		float falloffDistance;
		float decayRate;      // How much the strength decreases per frame
	};

private:
	std::vector<Particle> particles;
	const sf::Vector2f gravity = { 0.0f, 30.0f };

	bool isColliding(const Particle& p1, const Particle& p2);
	void resolveCollision(Particle& p1, Particle& p2);

	std::vector<ForceEffect> activeForces; // Track all active forces
};