#include <iostream>

#include "spatial_grid.hpp"
#include "grid_cell.hpp"
#include "particle_manager.hpp"



void SpatialGrid::initialize()
{
	gridSize = (SCREEN_WIDTH / 1) * (SCREEN_HEIGHT / 1);
	cells.resize(gridSize);
	std::cout << cells.size() << std::endl;
}

void SpatialGrid::clearGrid() 
{
	grid.clear();
}

std::pair<int, int> SpatialGrid::getCellCoordinates(const sf::Vector2f& position) 
{
	int cellX = static_cast<int>(position.x / 1);
	int cellY = static_cast<int>(position.y / 1);
	return { cellX, cellY };
}

const std::vector<Particle*>& SpatialGrid::getNeighbors(const sf::Vector2f& position) 
{
	std::vector<Particle*> neighbors;
	auto cell = getCellCoordinates(position);

	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			auto neighborCell = std::make_pair(cell.first + dx, cell.second + dy);
			if (grid.find(neighborCell) != grid.end()) {
				neighbors.insert(neighbors.end(), grid[neighborCell].begin(), grid[neighborCell].end());
			}
		}
	}
	return neighbors;
}

void SpatialGrid::addParticle(Particle* particle) 
{
	auto cell = getCellCoordinates(particle->currentPosition);
	
	grid[cell].push_back(particle);
}

// With a list of cells
int SpatialGrid::getCellIndex(sf::Vector2f particlePos)
{
	int gridWidth = SCREEN_WIDTH;

	int cellIndex = particlePos.x + (SCREEN_WIDTH * particlePos.y);
	return cellIndex;
}

void SpatialGrid::addParticleToGrid(Particle* particle)
{
	int cellIndex = getCellIndex(particle->currentPosition);

	cells[cellIndex].addParticleToCell(particle);
}

void SpatialGrid::clearCells()
{
	// Clear each cell
	for (GridCell cell : cells)
	{
		cell.clearParticles();
	}

	
}
