#include "Keyboard.hpp"

Keyboard::Keyboard()
{
	std::memset(_keys, 0, sizeof(_keys));
	std::memset(_prevKeys, 0, sizeof(_prevKeys));
}

Keyboard& Keyboard::getInstance()
{
	static Keyboard instance;

	return instance;
}


void Keyboard::setupKeyboard(GLFWwindow* window)
{
	glfwSetKeyCallback(window, callback);
}

bool Keyboard::keyChanged(int key)
{
	bool ret = _prevKeys[key];
	_prevKeys[key] = false;
	return ret;
}

bool Keyboard::isKeyDown(int key) const
{
	return _keys[key];
}

bool Keyboard::KeyWentDown(int key)
{
	return _keys[key] && keyChanged(key);
}

bool Keyboard::KeyWentUp(int key)
{
	return !_keys[key] && keyChanged(key);
}

void Keyboard::callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Keyboard& keyboard = getInstance();

	keyboard._keys[key] = action != GLFW_RELEASE;

	keyboard._prevKeys[key] = action != GLFW_REPEAT;
}
