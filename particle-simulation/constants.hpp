#pragma once

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const float PARTICLE_RADIUS = 0.5f;
const float PARTICLE_DIAMETER = 1;
const int SCREEN_MARGIN = 10; // Double particle radius
const float PARTICLE_MASS = 1.0f;

const int MAX_PARTICLE_COUNT = 2000;

const int CELL_SIZE = PARTICLE_RADIUS * 2;
const int CELL_COUNT = (SCREEN_WIDTH / CELL_SIZE) * (SCREEN_HEIGHT / CELL_SIZE);

const float EPSILON = 0.0001f;