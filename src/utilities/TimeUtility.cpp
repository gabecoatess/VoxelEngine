// TimeUtility.cpp

#include "TimeUtility.h"

#include <GLFW/glfw3.h>

TimeUtility& TimeUtility::GetInstance()
{
	static TimeUtility instance;
	return instance;
}

TimeUtility::TimeUtility() : deltaTime(0.0f), lastFrameTime(0.0f) {}

TimeUtility::~TimeUtility() {}

void TimeUtility::Initialize()
{
	lastFrameTime = static_cast<float>(glfwGetTime());
	deltaTime = 0.0f;
}

void TimeUtility::Update()
{
	float currentFrameTime = static_cast<float>(glfwGetTime());
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
}

float TimeUtility::GetDeltaTime() const
{
	return deltaTime;
}

void TimeUtility::Destroy()
{
	// N/A
}