#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <vector>

#include "../Utilities/Utilities.h"
#include "../graphics/Shader.hpp"

constexpr glm::vec2 gravity = glm::vec2(0, 9.81f);

enum class ParticleType
{
	Circle = 0
};

class Particle
{
protected:
	glm::vec2 size;
	glm::mat4 model;
	glm::vec3 color;
	unsigned int VAO, VBO;

public:
	glm::vec2 pos;
	glm::vec2 velocity;
	float lifeTime;
	float currentLifeTime;

	Particle(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, std::vector<float>& vertices);
	virtual void Update(double& dt);
	virtual void Render(Shader& shader) = 0;
	
	void cleanup();
};

class Circle : public Particle
{
public:
	Circle(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity);
	void Render(Shader& shader) override;

private:
	static std::vector<float> vertices;
};