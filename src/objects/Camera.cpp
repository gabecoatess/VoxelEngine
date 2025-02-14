// Camera.cpp

#include "Camera.h"
#include "../utilities/Renderer.h"
#include <cmath>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float aspectRatio, float nearPlane, float farPlane)
	: position(position)
	, worldUp(up)
	, yaw(yaw)
	, pitch(pitch)
	, front(glm::vec3(0.0f, 0.0f, -1.0f))
	, movementSpeed(SPEED)
	, mouseSensitivity(SENSITIVITY)
	, fieldOfView(FIELD_OF_VIEW)
	, aspectRatio(aspectRatio)
	, nearPlane(nearPlane)
	, farPlane(farPlane)
{
	Renderer::AddCamera(*this);
	UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float aspectRatio, float nearPlane, float farPlane)
	: Camera(glm::vec3(posX, posY, posZ), glm::vec3(upX, upY, upZ), yaw, pitch, aspectRatio, nearPlane, farPlane)
{
}

void Camera::Initialize()
{
	Renderer::AddCamera(*this);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

void Camera::SetAspectRatio(float width, float height)
{
	aspectRatio = width / height;
}

void Camera::SetFieldOfView(float fov)
{
	fieldOfView = fov;
}

void Camera::SetClipPlanes(float near, float far)
{
	nearPlane = near;
	farPlane = far;
}

void Camera::SetNearPlane(float near)
{
	nearPlane = near;
}

void Camera::SetFarPlane(float far)
{
	farPlane = far;
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