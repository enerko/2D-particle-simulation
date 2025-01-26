#pragma once

#include <iostream>
#include <vector>
#include "particle.hpp"

class GridCell
{
public:
	std::vector<Particle*> particles;

	void addParticleToCell(Particle* particle);
	void clearParticles();
};