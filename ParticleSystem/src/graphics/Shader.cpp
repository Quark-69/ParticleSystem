#include "Shader.hpp"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	generateShader(vertexShaderPath, fragmentShaderPath);
}

void Shader::generateShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	int success;
	char infoLog[512];

	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	programId = glCreateProgram();

	glAttachShader(programId, vertexShader);
	glAttachShader(programId, fragmentShader);
	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(programId, 512, nullptr, infoLog);
		std::cout << "Error linking shader: " << infoLog << '\n';
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(programId);
}

void Shader::activate() const
{
	glUseProgram(programId);
}

void Shader::setMat4(std::string name, glm::mat4 val) const
{
	glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, value_ptr(val));
}

void Shader::setInt(std::string name, GLint val) const
{
	glUniform1i(glGetUniformLocation(programId, name.c_str()), val);
}

void Shader::setFloat(std::string name, float val) const
{
	glUniform1f(glGetUniformLocation(programId, name.c_str()), val);
}

void Shader::setFloat3(std::string name, glm::vec3 val) const
{
	setFloat3(name, val.x, val.y, val.z);
}

void Shader::setFloat3(std::string name, float v1, float v2, float v3) const
{
	glUniform3f(glGetUniformLocation(programId, name.c_str()), v1, v2, v3);
}

void Shader::setFloat4(std::string name, aiColor4D color)
{
	setFloat4(name, color.r, color.g, color.b, color.a);
}

void Shader::setFloat4(std::string name, glm::vec4 val)
{
	setFloat4(name, val.x, val.y, val.z, val.w);
}

void Shader::setFloat4(std::string name, float v1, float v2, float v3, float v4) const
{
	glUniform4f(glGetUniformLocation(programId, name.c_str()), v1, v2, v3, v4);
}

std::string Shader::loadShaderSrc(const char* fileName)
{
	std::ifstream file;
	std::stringstream buf;

	std::string ret;

	file.open(fileName);

	if (file.is_open())
	{
		buf << file.rdbuf();
		ret = buf.str();
	}
	else
	{
		std::cout << "Could not read " << fileName << '\n';
	}

	file.close();

	return ret;
}

GLuint Shader::compileShader(const char* shaderPath, GLenum type)
{
	int success;
	char infoLog[512];

	GLuint ret = glCreateShader(type);
	std::string shaderSrc = loadShaderSrc(shaderPath);
	const GLchar* retShader = shaderSrc.c_str();
	glShaderSource(ret, 1, &retShader, nullptr);
	glCompileShader(ret);

	glGetShaderiv(ret, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(ret, 512, nullptr, infoLog);
		std::cout << "Error with compiling shader: " << infoLog << std::endl;
	}

	return ret;
}
