// Renderer.h

#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "../objects/Camera.h"

class Renderer
{
public:
	static void Initialize();
	static void Initialize(Camera& camera);
	
	static void SetViewport(float width, float height);
	static void ClearScreen(const glm::vec4& color);

	static void DrawMesh(const Mesh& mesh, const Shader& shader, const glm::mat4& modelMatrix);
	static void DrawMesh(const Mesh& mesh, const glm::mat4& modelMatrix);

	static Camera& GetCurrentCamera();
	static void SetCurrentCamera(Camera& camera) { currentCamera = &camera; }

	static void AddCamera(Camera& camera);
	static void RemoveCamera(Camera& camera);
	static const std::vector<Camera*>& GetCameras() { return cameras; }
	static void ClearCameras();

	static void UpdateAllCamerasAspectRatio(float width, float height);

private:
	static Camera* currentCamera;
	static std::vector<Camera*> cameras;
	static Shader* defaultShader;
};

#endif