// Shader.h

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int Id;

	Shader(const char* vertexSourcePath, const char* fragmentSourcePath);

	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	void setVec2i(const std::string& name, int x, int y) const;
	void setVec2f(const std::string& name, float x, float y) const;

	void setVec3i(const std::string& name, int x, int y, int z) const;
	void setVec3f(const std::string& name, float x, float y, float z) const;

	void setVec4i(const std::string& name, int x, int y, int z, int w) const;
	void setVec4f(const std::string& name, float x, float y, float z, float w) const;

	void setMat4(const std::string& name, const glm::mat4& matrix) const;
};

#endif