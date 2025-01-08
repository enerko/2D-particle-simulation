#include "particle_manager.hpp"
#include "particle.hpp"

ParticleManager::ParticleManager()
{

}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::spawnParticle(sf::Vector2f position, sf::Vector2f velocity)
{
    Particle newParticle;
    newParticle.setPosition(position);
    newParticle.setVelocity(velocity);

    // Assign a random color
    newParticle.color = sf::Color(rand() % 256, rand() % 256, rand() % 256);

    particles.push_back(newParticle);
}

void ParticleManager::updateParticles(float deltaTime)
{
    // Make particles move downwards from gravity
    for (Particle& particle : particles)
    {
        particle.acceleration += gravity;
        particle.updateParticle(deltaTime);
    }

    // Check for collisions
    checkCollision(deltaTime);
}

void ParticleManager::render(sf::RenderWindow& renderer)
{
    for (Particle& particle : particles)
    {
        sf::CircleShape shape(PARTICLE_RADIUS);
        shape.setPosition(particle.currentPosition);
        shape.setFillColor(particle.color);

        renderer.draw(shape);
    }
}

void ParticleManager::checkCollision(float deltaTime)
{
    for (size_t i = 0; i < particles.size(); i++)
    {
        for (size_t j = i + 1; j < particles.size(); j++)
        {
            if (isColliding(particles[i], particles[j]))
            {
                resolveCollision(particles[i], particles[j]);
            }
        }
    }
}

bool ParticleManager::isColliding(const Particle& p1, const Particle& p2)
{
    sf::Vector2f delta = p1.currentPosition - p2.currentPosition;
    float distanceSquared = delta.x * delta.x + delta.y * delta.y;
    float radiiSum = PARTICLE_RADIUS * 2; 
    return distanceSquared < radiiSum * radiiSum;
}

void ParticleManager::resolveCollision(Particle& p1, Particle& p2)
{
    sf::Vector2f delta = p1.currentPosition - p2.currentPosition;
    float distanceSquared = delta.x * delta.x + delta.y * delta.y;

    float distance = std::sqrt(distanceSquared);
    float overlap = 2 * PARTICLE_RADIUS - distance;

    // Get the normalized direction vector from p2 to p1
    sf::Vector2f direction = delta / distance;

    // Apply collision forces
    const float k = 80.0f; // Spring constant for Hooke's Law Force = -k x distance
    sf::Vector2f force = k * overlap * direction;

    p1.acceleration += force / PARTICLE_MASS; // Force = mass x acceleration
    p2.acceleration -= force / PARTICLE_MASS;

    // Adjust position by half of overlap in the axis of the direction vector
    p1.currentPosition += (direction * overlap * 0.5f);
    p2.currentPosition -= (direction * overlap * 0.5f);
}

void ParticleManager::createForce(sf::Vector2f forcePosition, float initialStrength, float falloffDistance, float decayRate)
{
    activeForces.push_back(ForceEffect{ forcePosition, initialStrength, falloffDistance, decayRate });
}

void ParticleManager::updateForces(float deltaTime)
{
    // Iterate through active forces and apply them
    for (auto it = activeForces.begin(); it != activeForces.end();)
    {
        const auto& force = *it;

        // Apply force to all particles
        for (auto& particle : particles)
        {
            sf::Vector2f direction = particle.currentPosition - force.position;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance <= force.falloffDistance)
            {
                // Calculate force magnitude based on proximity
                float strength = force.strength * (1.0f - (distance / force.falloffDistance));
                sf::Vector2f scaledForce = (direction / distance) * strength;

                particle.applyForce(scaledForce);
            }
        }

        // Decay the force strength
        it->strength -= it->decayRate * deltaTime;

        // Remove forces that have decayed to zero or less
        if (it->strength <= 0.0f)
            it = activeForces.erase(it);
        else
            ++it;
    }
}