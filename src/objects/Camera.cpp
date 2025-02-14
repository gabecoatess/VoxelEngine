// Camera.cpp

#include "Camera.h"
#include <cmath>

Camera::Camera(glm::vec3 _position, glm::vec3 _up, float _yaw, float _pitch)
	: front(glm::vec3(0.0f, 0.0f, -1.0f)),
	movementSpeed(SPEED),
	mouseSensitivity(SENSITIVITY),
	fieldOfView(FIELD_OF_VIEW)
{
	position = _position;
	worldUp = _up;
	yaw = _yaw;
	pitch = _pitch;

	UpdateCameraVectors();
}

Camera::Camera(float _posX, float _posY, float _posZ, float _upX, float _upY, float _upZ, float _yaw, float _pitch)
	: front(glm::vec3(0.0f, 0.0f, -1.0f)),
	movementSpeed(SPEED),
	mouseSensitivity(SENSITIVITY),
	fieldOfView(FIELD_OF_VIEW)
{
	position = glm::vec3(_posX, _posY, _posZ);
	worldUp = glm::vec3(_upX, _upY, _upZ);
	yaw = _yaw;
	pitch = _pitch;

	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(Camera_Movement _direction, float _deltaTime)
{
	float velocity = movementSpeed * _deltaTime;
	
	if (_direction == FORWARD)
	{
		position += front * velocity;
	}

	if (_direction == BACKWARD)
	{
		position -= front * velocity;
	}

	if (_direction == LEFT)
	{
		position -= right * velocity;
	}

	if (_direction == RIGHT)
	{
		position += right * velocity;
	}

	if (_direction == UP)
	{
		position += up * velocity;
	}

	if (_direction == DOWN)
	{
		position -= up * velocity;
	}
}

void Camera::ProcessMouseMovement(float _xOffset, float _yOffset, GLboolean _constrainPitch)
{
	_xOffset *= mouseSensitivity;
	_yOffset *= mouseSensitivity;

	yaw += _xOffset;
	pitch += _yOffset;

	if (_constrainPitch)
	{
		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}

		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}
	}

	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float _yOffset)
{
	fieldOfView -= _yOffset;

	if (fieldOfView < 1.0f)
	{
		fieldOfView = 1.0f;
	}

	if (fieldOfView > 110.0f)
	{
		fieldOfView = 110.0f;
	}
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 _front;

	_front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	_front.y = std::sin(glm::radians(pitch));
	_front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));

	front = glm::normalize(_front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}