// Chunk.h

#ifndef CHUNK_H
#define CHUNK_H

#include "../engine/MultiDimArray.h"
#include "../utilities/Mesh.h"

class Chunk
{
public:
	static constexpr size_t CHUNK_WIDTH = 16;
	static constexpr size_t CHUNK_HEIGHT = 16;
	static constexpr size_t CHUNK_DEPTH = 16;

	Chunk();
	~Chunk();

	void GenerateData();

	Mesh GenerateMesh() const;

	const MultiDimArray& GetData() const;

private:
	MultiDimArray _data;
};

#endif