#include "particle_manager.hpp"
#include "particle.hpp"

ParticleManager::ParticleManager()
{

}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::spawnParticles(sf::Vector2f position)
{
    Particle newParticle;
    newParticle.setPosition(position);

    particles.push_back(newParticle);
}

void ParticleManager::updateParticles(float deltaTime)
{
    for (Particle& particle : particles)
    {
    
        particle.acceleration = gravity;
        particle.updateParticle(deltaTime);
    }
}

void ParticleManager::render(sf::RenderWindow& renderer)
{
    for (Particle& particle : particles)
    {
        sf::CircleShape shape(5.0f);
        shape.setPosition(particle.currentPostion);
        shape.setFillColor(sf::Color::White);

        renderer.draw(shape);
    }
}