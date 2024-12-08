#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "../io/Keyboard.hpp"
#include "../io/Mouse.hpp"
#include "../graphics/Shader.hpp"

class App
{
private:
	Window* window_;
	Keyboard* keyboard_;
	Mouse* mouse_;

	double dt;
	double lastFrame;

	void processInput() const;
	void updateDt();

public:
	App(Window* window);
	void Run();
};
