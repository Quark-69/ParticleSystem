#pragma once

#include "Particle.h"
#include <random>
#include "../Engine/Window.hpp"
#include "../io/Mouse.hpp"

class ParticleSystem
{

public:
	ParticleSystem(Window* window, Mouse* mouse);
	void Render(Shader& shader);
	void Update();
	void cleanup();
	void AddParticles(unsigned int count, ParticleType type);

private:
	Window* window_;
	Mouse* mouse_;
	std::vector<Particle*> particles;
	void generateCircles(unsigned int count);

	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> colorGen;
};