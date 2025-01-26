#pragma once

#include <unordered_map>
#include <vector>
#include <cmath>
#include "particle.hpp"
#include "pair_hash.hpp"
#include "grid_cell.hpp"

// Spatial grid for collision optimization using spatial partitioning
class SpatialGrid
{
public:
	void initialize();
	// int cellSize = 4;

	std::vector<GridCell> cells; // List of cells

	std::unordered_map<std::pair<int, int>, std::vector<Particle*>, PairHash> grid; // List of 

	void addParticleToGrid(Particle* particle);
	void clearGrid();

	std::vector<Particle*> getNeighbors(sf::Vector2f particlePos);

	std::pair<int, int> getCellCoordinates(const sf::Vector2f& position);

	const std::vector<Particle*>& getNeighbors(const sf::Vector2f& position);

	void addParticle(Particle* particle);

	std::vector<Particle*> getNeighborsWithIndex(const GridCell& cell, int index);

	void clearCells();

	

private:
	
	int getCellIndex(sf::Vector2f particlePos);
	int gridSize;
};


