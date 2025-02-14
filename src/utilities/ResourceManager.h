// ResourceManager.h

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "Shader.h"

class ResourceManager
{
public:
	static Shader* LoadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name);

	static Shader* GetShader(const std::string& name);

	static void ClearShaders();

private:
	static std::map<std::string, std::unique_ptr<Shader>> Shaders;
};

#endif