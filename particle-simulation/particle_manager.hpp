#pragma once

#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "constants.hpp"
#include "spatial_grid.hpp"

class ParticleManager
{
public: 
	ParticleManager();
	~ParticleManager();

	void initialize();

	void spawnParticle(sf::Vector2f position, sf::Vector2f velocity);
	void updateParticles(float deltaTime);
	void render(sf::RenderWindow& renderer);
	void checkCollision(float deltaTime);
	void checkCollisionSpatial(float deltaTime);

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

	bool isColliding(const Particle& p1, const Particle& p2);
	void resolveCollision(Particle& p1, Particle& p2);

	void processCell(GridCell& cell, int index);
	void checkCellCollision(Particle& p, GridCell& cell);

private:
	std::vector<Particle> particles;
	const sf::Vector2f gravity = { 0.0f, 30.0f };

	std::vector<ForceEffect> activeForces; // Track all active forces
	SpatialGrid spatialGrid;
};