#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(Window* window, Mouse* mouse)
	: window_(window), mouse_(mouse), rng(rd()), particles({}), colorGen(0.0f, 1.0f)
{
}

void ParticleSystem::Render(Shader& shader)
{
	for (auto& x : particles)
	{
		x->Render(shader);
	}
}

void ParticleSystem::Update()
{
	for (auto& x : particles)
	{
		x->Update();
	}
}

void ParticleSystem::cleanup()
{
	for (auto& part : particles)
	{
		part->cleanup();
		delete part;
	}
}

void ParticleSystem::AddParticles(unsigned int count, ParticleType type)
{
	if (type == ParticleType::Circle)
	{
		generateCircles(count);
	}
}

void ParticleSystem::generateCircles(unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{

		glm::vec2 pos = glm::vec2(
			window_->getSreenWidth() / 2.0f,
			window_->getSreenHeight() / 2.0f
		);

		glm::vec2 size = glm::vec2(1.0f);

		glm::vec3 color = glm::vec3(
			colorGen(rng),
			colorGen(rng),
			colorGen(rng)
		);

		Circle* cirle = new Circle(pos, size, color);

		particles.emplace_back(cirle);
	}
}
