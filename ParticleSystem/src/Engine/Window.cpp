#include "Window.hpp"

Window::Window(int sWidth, int sHeight, const char* title, Camera camera)
	: screenWidth(sWidth), screenHeight(sHeight), window(nullptr), camera(camera)
{
	setupWindow(title);
}

bool Window::setupWindow(const char* title)
{
	window = glfwCreateWindow(screenWidth, screenHeight, title, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << "\n";
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);

	return true;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	auto instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (instance)
	{
		instance->OnFramebufferSizeChange(width, height);
	}
}

void Window::setParams() const
{
	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_DEPTH_TEST);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
}

void Window::OnFramebufferSizeChange(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}

bool Window::shouldWindowClose() const
{
	return glfwWindowShouldClose(window);
}

void Window::setWindowShouldClose(bool close) const
{
	glfwSetWindowShouldClose(window, close);
}

void Window::update()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::newFrame() const
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int Window::getSreenWidth() const
{
	return screenWidth;
}

int Window::getSreenHeight() const
{
	return screenHeight;
}

GLFWwindow* Window::getWindow() const
{
	return window;
}

Camera& Window::getCamera()
{
	return camera;
}
