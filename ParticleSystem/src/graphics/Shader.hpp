#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <streambuf>

#include <assimp/scene.h>

class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void generateShader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void activate() const;
	void setMat4(std::string name, glm::mat4 val) const;
	void setInt(std::string name, GLint val) const;
	void setFloat(std::string name, float val) const;
	void setFloat3(std::string name, glm::vec3 val) const;
	void setFloat3(std::string name, float v1, float v2, float v3) const;
	void setFloat4(std::string name, aiColor4D color);
	void setFloat4(std::string name, glm::vec4 val);
	void setFloat4(std::string name, float v1, float v2, float v3, float v4) const;
	~Shader();

	GLuint programId;

private:
	static std::string loadShaderSrc(const char* fileName);
	static GLuint compileShader(const char* shaderPath, GLenum type);
};
