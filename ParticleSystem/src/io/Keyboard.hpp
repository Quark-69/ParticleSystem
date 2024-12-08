#pragma once

#include <GLFW/glfw3.h>
#include <cstring>

class Keyboard
{
	Keyboard();
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	bool _keys[GLFW_KEY_LAST];
	bool _prevKeys[GLFW_KEY_LAST];

public:
	static Keyboard& getInstance();


	bool keyChanged(int key);

	bool isKeyDown(int key) const;

	bool KeyWentDown(int key);
	bool KeyWentUp(int key);

	static void setupKeyboard(GLFWwindow* window);
	static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
