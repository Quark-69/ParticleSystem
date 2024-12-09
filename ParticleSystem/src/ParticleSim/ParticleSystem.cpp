#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(Window* window, Mouse* mouse)
	: window_(window), mouse_(mouse), rng(rd()), particles({}), colorGen(0.0f, 1.0f), speedGen(10.0f, 50.0f), angleGen(0, 360)
{
}

void ParticleSystem::Render(Shader& shader)
{
	for (auto& x : particles)
	{
		x->Render(shader);
	}
}

void ParticleSystem::Update(double& dt)
{
	for (auto& x : particles)
	{
		x->currentLifeTime -= (float)dt;

		if (x->currentLifeTime <= 0.0f)
		{
			resetParticle(x);
		}

		x->Update(dt);
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

		float angle = glm::radians(static_cast<float>(angleGen(rng)));
		float speed = speedGen(rng);

		glm::vec2 vel = glm::vec2(speed * glm::cos(angle), speed * glm::sin(angle));

		Circle* cirle = new Circle(pos, size, color, vel);

		particles.emplace_back(cirle);
	}
}

void ParticleSystem::resetParticle(Particle* particle)
{
	float angle = glm::radians(static_cast<float>(angleGen(rng)));
	float speed = speedGen(rng);
	particle->velocity = glm::vec2(speed * glm::cos(speed), speed * glm::sin(speed));
	particle->pos = glm::vec2(mouse_->getMouseX(), mouse_->getMouseY());
	particle->currentLifeTime = particle->lifeTime;
}
