#include "Particle.h"

std::vector<float> Circle::vertices = Utility::generateCircleVertices(500, 5);

Particle::Particle(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, std::vector<float>& vertices)
	:pos(pos), size(size), color(color), velocity(velocity), lifeTime(5.0f), model(glm::mat4(1.0f)), currentLifeTime(lifeTime)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Particle::Update(double& dt)
{
	velocity += float(dt) * gravity;
	pos += float(dt) * velocity;

	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::scale(model, glm::vec3(size, 0.0f));
}

void Particle::cleanup()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

Circle::Circle(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity)
	: Particle(pos, size, color, velocity, vertices)
{

}

void Circle::Render(Shader& shader)
{
	shader.setMat4("model", model);
	shader.setFloat4("color", glm::vec4(color, currentLifeTime / lifeTime));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, (int)ceil(vertices.size() / 2.0));
	glBindVertexArray(0);
}
