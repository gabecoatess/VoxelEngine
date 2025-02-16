// Renderer.cpp

#include "Renderer.h"
#include "ResourceManager.h"

#include <glad/glad.h>

std::vector<Camera*> Renderer::cameras;
Camera* Renderer::currentCamera = nullptr;
Shader* Renderer::defaultShader = nullptr;

void Renderer::Initialize()
{
	// DEPTH TESTING
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	currentCamera = nullptr;
}

void Renderer::Initialize(Camera& camera)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	currentCamera = &camera;

	defaultShader = ResourceManager::LoadShader("default_vertex.glsl", "default_fragment.glsl", "default");
}

void Renderer::SetViewport(float width, float height)
{
	glViewport(0, 0, width, height);
}

void Renderer::ClearScreen(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawMesh(const Mesh& mesh, const Shader& shader, const glm::mat4& modelMatrix)
{
	if (!currentCamera) {
		throw std::runtime_error("No camera has been set! Please set a camera before drawing.");
	}

	shader.use();

	glm::mat4 mvp = currentCamera->GetProjectionMatrix() * currentCamera->GetViewMatrix() * modelMatrix;
	shader.setMat4("sMatrices", mvp);
	mesh.Draw();
}

void Renderer::DrawMesh(const Mesh& mesh, const glm::mat4& modelMatrix)
{
	DrawMesh(mesh, *defaultShader, modelMatrix);
}

Camera& Renderer::GetCurrentCamera()
{
	if (!currentCamera)
	{
		throw std::runtime_error("[ERROR] No camera has been found!");
	}

	return *currentCamera;
}

void Renderer::AddCamera(Camera& camera)
{
	if (std::find(cameras.begin(), cameras.end(), &camera) == cameras.end())
	{
		cameras.push_back(&camera);
	}
}

void Renderer::RemoveCamera(Camera& camera)
{
	auto it = std::find(cameras.begin(), cameras.end(), &camera);

	if (it != cameras.end())
	{
		if (currentCamera == &camera)
		{
			if (cameras.size() > 1)
			{
				currentCamera = (cameras.front() == &camera) ? cameras[1] : cameras.front();
			}
			else
			{
				currentCamera = nullptr;
			}
		}

		cameras.erase(it);
	}
}

void Renderer::ClearCameras()
{
	cameras.clear();
	currentCamera = nullptr;
}

void Renderer::UpdateAllCamerasAspectRatio(float width, float height)
{
	for (Camera* camera : cameras)
	{
		camera->SetAspectRatio(width, height);
	}
}