#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>


enum class CameraDirection
{
	Forward = 0,
	Backward,
	Left,
	Right,
	Up,
	Down
};

class Camera
{
public:
	Camera(glm::vec3 pos);

	void updateCamera();

	void updateCameraPos(CameraDirection dir, double dt);

	void updateCameraDirection(double dx, double dy);

	void updateCameraZoom(double dy);

	glm::mat4 getViewMatrix() const;

	float getZoom() const;

	const glm::vec3& getPos() const;
	const glm::vec3& getFront() const;

private:
	float yaw, pitch;

	float speed;
	float sensitivity;
	float zoom;

	glm::vec3 positon;
	glm::vec3 front;
	glm::vec3 worldUp;
	glm::vec3 up;
	glm::vec3 right;
};
