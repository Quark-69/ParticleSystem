#include "Mouse.hpp"

void Mouse::cursorPosCallback(GLFWwindow* window, double _x, double _y)
{
	Mouse& mouse = getInstance();

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	mouse.x = _x;
	mouse.y = _y;


	mouse.x_ndc = 2.0 * (mouse.x / width) - 1.0;
	mouse.y_ndc = 1.0 - 2.0 * (mouse.y / height);

	if (mouse.firstMouse)
	{
		mouse.lastX = mouse.x;
		mouse.lastY = mouse.y;
		mouse.firstMouse = false;
	}

	mouse.dx = mouse.x - mouse.lastX;
	mouse.dy = mouse.lastY - mouse.y;

	mouse.lastX = mouse.x;
	mouse.lastY = mouse.y;
}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Mouse& mouse = getInstance();

	mouse.buttons[button] = action != GLFW_RELEASE;
	mouse.prevButtons[button] = action != GLFW_REPEAT;
}

void Mouse::mouseWheelCallback(GLFWwindow* window, double dx, double dy)
{
	Mouse& mouse = getInstance();
	mouse.scrollDX = dx;
	mouse.scrollDY = dy;
}

void Mouse::setupMouse(GLFWwindow* window)
{
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetScrollCallback(window, mouseWheelCallback);
}

Mouse& Mouse::getInstance()
{
	static Mouse instance;

	return instance;
}

double Mouse::getMouseX() const
{
	return x;
}

double Mouse::getMouseY() const
{
	return y;
}

double Mouse::getMouseX_NDC() const
{
	return x_ndc;
}

double Mouse::getMouseY_NDC() const
{
	return y_ndc;
}

double Mouse::getDX()
{
	double _dx = dx;
	dx = 0;
	return _dx;
}

double Mouse::getDY()
{
	double _dy = dy;
	dy = 0;
	return _dy;
}

double Mouse::getScrollDX()
{
	double _scrollDX = scrollDX;
	scrollDX = 0;
	return _scrollDX;
}

double Mouse::getScrollDY()
{
	double _scrollDY = scrollDY;
	scrollDY = 0;
	return _scrollDY;
}

bool Mouse::isButtonDown(int _button) const
{
	return buttons[_button];
}

bool Mouse::buttonChanged(int _button)
{
	bool ret = prevButtons[_button];
	prevButtons[_button] = false;
	return ret;
}

bool Mouse::buttonWentUp(int _button)
{
	return !buttons[_button] && buttonChanged(_button);
}

bool Mouse::buttonWentDown(int _button)
{
	return buttons[_button] && buttonChanged(_button);
}

Mouse::Mouse()
	: x(0), y(0), lastX(0), lastY(0), dx(0), dy(0), scrollDX(0), scrollDY(0), firstMouse(true), x_ndc(0), y_ndc(0)
{
	std::memset(buttons, 0, sizeof(buttons));
	std::memset(prevButtons, 0, sizeof(prevButtons));
}
