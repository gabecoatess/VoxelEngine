// Mesh.h

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glad/glad.h>

class Mesh
{
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int vertexArrayObject;

	Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

	void Draw() const;

	~Mesh();

private:
	unsigned int vertexBufferObject;
	unsigned int elementBufferObject;

	void SetupMesh();
};

#endif