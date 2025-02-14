// Mesh.cpp

#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
	: vertices(vertices), indices(indices)
{
	SetupMesh();
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &vertexBufferObject);
	glGenBuffers(1, &elementBufferObject);

	glBindVertexArray(vertexArrayObject);

	// Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// Element Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// [Attribute 0] Position (3 floats)
	// [Attribute 1] Color (3 floats)
	// [Attribute 2] Tex Coords (2 floats)

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Mesh::Draw() const
{
	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &elementBufferObject);
}