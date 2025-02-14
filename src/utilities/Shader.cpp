// Shader.cpp

#include "Shader.h"

Shader::Shader(const char* vertexSourcePath, const char* fragmentSourcePath)
{
	// Retrieve data from path
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open
		vShaderFile.open(std::string(PROJECT_ROOT) + "/src/shaders/" + vertexSourcePath);
		fShaderFile.open(std::string(PROJECT_ROOT) + "/src/shaders/" + fragmentSourcePath);

		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		// Read
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close
		vShaderFile.close();
		fShaderFile.close();

		// Convert to string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// Compile shaders
	unsigned int vertexId;
	unsigned int fragmentId;

	int success;
	char infoLog[512];

	// Vertex Compilation
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &vShaderCode, NULL);
	glCompileShader(vertexId);

	// Print errors
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
	};

	// Fragment Compilation
	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &fShaderCode, NULL);
	glCompileShader(fragmentId);

	// Print errors
	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
	};

	// Create Shader Program
	Id = glCreateProgram();
	
	glAttachShader(Id, vertexId);
	glAttachShader(Id, fragmentId);
	glLinkProgram(Id);

	// Print errors
	glGetProgramiv(Id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(Id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
	}

	// Delete shaders
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void Shader::use() const
{
	glUseProgram(Id);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(Id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(Id, name.c_str()), value);
}

void Shader::setVec2i(const std::string& name, int x, int y) const
{
	glUniform2i(glGetUniformLocation(Id, name.c_str()), x, y);
}

void Shader::setVec2f(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(Id, name.c_str()), x, y);
}

void Shader::setVec3i(const std::string& name, int x, int y, int z) const
{
	glUniform3i(glGetUniformLocation(Id, name.c_str()), x, y, z);
}

void Shader::setVec3f(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(Id, name.c_str()), x, y, z);
}

void Shader::setVec4i(const std::string& name, int x, int y, int z, int w) const
{
	glUniform4i(glGetUniformLocation(Id, name.c_str()), x, y, z, w);
}

void Shader::setVec4f(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(Id, name.c_str()), x,y ,z, w);
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}