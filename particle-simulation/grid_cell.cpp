#include "grid_cell.hpp"

void GridCell::addParticleToCell(Particle* particle)
{
	particles.push_back(particle);
}

void GridCell::clearParticles()
{
	particles.clear();
}