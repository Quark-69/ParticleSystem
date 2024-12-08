#pragma once

#include <GLFW/glfw3.h>
#include <cstring>

class Mouse
{
	Mouse();
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	double x;
	double y;

	double x_ndc;
	double y_ndc;

	double lastX;
	double lastY;

	double dx;
	double dy;

	double scrollDX;
	double scrollDY;

	bool buttons[GLFW_MOUSE_BUTTON_LAST];
	bool prevButtons[GLFW_MOUSE_BUTTON_LAST];

	bool firstMouse;

public:
	static void cursorPosCallback(GLFWwindow* window, double _x, double _y);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseWheelCallback(GLFWwindow* window, double dx, double dy);
	static Mouse& getInstance();

	static void setupMouse(GLFWwindow* window);

	double getMouseX() const;
	double getMouseY() const;

	double getMouseX_NDC() const;
	double getMouseY_NDC() const;

	double getDX();
	double getDY();

	double getScrollDX();
	double getScrollDY();

	bool isButtonDown(int _button) const;
	bool buttonChanged(int _button);
	bool buttonWentUp(int _button);
	bool buttonWentDown(int _button);
};
