#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <vector>

#include "../Utilities/Utilities.h"
#include "../graphics/Shader.hpp"

enum class ParticleType
{
	Circle = 0
};

class Particle
{
protected:
	glm::vec2 pos;
	glm::vec2 size;
	glm::mat4 model;
	glm::vec3 color;
	unsigned int VAO, VBO;

public:
	Particle(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::vector<float>& vertices);
	virtual void Update();
	virtual void Render(Shader& shader) = 0;
	
	void cleanup();
};

class Circle : public Particle
{
public:
	Circle(glm::vec2 pos, glm::vec2 size, glm::vec3 color);
	void Render(Shader& shader) override;

private:
	static std::vector<float> vertices;
};