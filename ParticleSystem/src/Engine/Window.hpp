#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.hpp"

class Window
{
	int screenWidth;
	int screenHeight;
	GLFWwindow* window;
	Camera camera;

	bool setupWindow(const char* title);
	void OnFramebufferSizeChange(int width, int height);

public:
	Window(int sWidth, int sHeight, const char* title, Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f)));
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void setParams() const;
	bool shouldWindowClose() const;
	void setWindowShouldClose(bool close) const;
	void update();
	void newFrame() const;

	int getSreenWidth() const;
	int getSreenHeight() const;
	GLFWwindow* getWindow() const;
	Camera& getCamera();
};
