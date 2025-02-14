// ResourceManager.cpp

#include "ResourceManager.h"

#include <stdexcept>
#include <iostream>

std::map<std::string, std::unique_ptr<Shader>> ResourceManager::Shaders;

Shader* ResourceManager::LoadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name)
{
    std::unique_ptr<Shader> shader = std::make_unique<Shader>(vertexPath.c_str(), fragmentPath.c_str());
    Shader* shaderPtr = shader.get();
    Shaders.emplace(name, std::move(shader));
    return shaderPtr;
}

Shader* ResourceManager::GetShader(const std::string& name)
{
    auto it = Shaders.find(name);
    if (it == Shaders.end())
    {
        std::cerr << "ERROR: Shader with name '" << name << "' not found." << std::endl;
        throw std::runtime_error("Shader not found!");
    }
    return it->second.get();
}

void ResourceManager::ClearShaders()
{
    Shaders.clear();
}