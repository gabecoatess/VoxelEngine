// Camera.h

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*
glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(currentWinWidth) / static_cast<float>(currentWinHeight), 0.1f, 100.0f);
glm::mat4 viewMatrix = camera.GetViewMatrix();
*/

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FIELD_OF_VIEW = 90.0f;
const float NEAR_PLANE = 0.01f;
const float FAR_PLANE = 1000.0f;

class Camera
{
public:
	// Camera Attributes
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;
	float fieldOfView;

	float aspectRatio;
	float nearPlane;
	float farPlane;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float aspectRatio = 800.0f / 600.0f, float nearPlane = NEAR_PLANE, float farPlane = FAR_PLANE);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float aspectRatio = 800.0f / 600.0f, float nearPlane = NEAR_PLANE, float farPlane = FAR_PLANE);

	void Initialize();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	void SetAspectRatio(float width, float height);
	void SetFieldOfView(float fieldOfView);
	void SetClipPlanes(float near, float far);
	void SetNearPlane(float near);
	void SetFarPlane(float far);

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yOffset);

	void UpdateCameraVectors();
};

#endif