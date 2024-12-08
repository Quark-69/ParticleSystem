#include "Camera.hpp"

Camera::Camera(glm::vec3 pos)
	: yaw(-90.0f), pitch(0.0f), speed(2.5f), sensitivity(0.1f), zoom(45.0f), positon(pos),
	  front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f)
{
	worldUp = up;
	right = glm::vec3(0, 0, 0);

	updateCamera();
}

void Camera::updateCamera()
{
	glm::vec3 _front;
	_front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	_front.y = glm::sin(glm::radians(pitch));
	_front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

	front = normalize(_front);

	right = normalize(cross(front, worldUp));
	up = normalize(cross(right, front));
}

void Camera::updateCameraPos(CameraDirection dir, double dt)
{
	float adjustedSpeed = static_cast<float>(dt) * speed;

	switch (dir)
	{
	case CameraDirection::Forward:
		positon += adjustedSpeed * front;
		break;

	case CameraDirection::Backward:
		positon -= adjustedSpeed * front;
		break;

	case CameraDirection::Right:
		positon += adjustedSpeed * right;
		break;

	case CameraDirection::Left:
		positon -= adjustedSpeed * right;
		break;

	case CameraDirection::Up:
		positon += adjustedSpeed * up;
		break;

	case CameraDirection::Down:
		positon -= adjustedSpeed * up;
		break;
	}
}

void Camera::updateCameraDirection(double dx, double dy)
{
	yaw += static_cast<float>(dx) * sensitivity;
	pitch += static_cast<float>(dy) * sensitivity;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	updateCamera();
}

void Camera::updateCameraZoom(double dy)
{
	zoom -= static_cast<float>(dy);
	if (zoom < 1.0f)
		zoom = 1.0f;
	else if (zoom > 45.0f)
		zoom = 45.0f;
}

glm::mat4 Camera::getViewMatrix() const
{
	return lookAt(positon, positon + front, up);
}

float Camera::getZoom() const
{
	return zoom;
}

const glm::vec3& Camera::getPos() const
{
	return positon;
}

const glm::vec3& Camera::getFront() const
{
	return front;
}
