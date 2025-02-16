// Chunk.h

#ifndef CHUNK_H
#define CHUNK_H

#include "../engine/MultiDimArray.h"
#include "../utilities/Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

class Chunk
{
public:
	static constexpr size_t CHUNK_WIDTH = 16;
	static constexpr size_t CHUNK_HEIGHT = 16;
	static constexpr size_t CHUNK_DEPTH = 16;

	Chunk(const glm::ivec3& gridPosition);
	~Chunk();

	void GenerateData();

	void UpdateMesh();

	const Mesh* GetMesh() const;
	const MultiDimArray& GetData() const;
	glm::mat4 GetModelMatrix() const;

private:
	glm::ivec3 _gridPosition;
	MultiDimArray _data;
	std::unique_ptr<Mesh> _mesh;
};

#endif