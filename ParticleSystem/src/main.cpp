#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Engine/Window.hpp"
#include "Engine/App.hpp"


int main(int argc, char** argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window window(800, 600, "OpenGL Window");

	try
	{
		App app(&window);
		app.Run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	glfwTerminate();

	return 0;
}
