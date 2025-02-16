// Chunk.cpp

#include "Chunk.h"

#include <vector>

Chunk::Chunk()
	: _data(CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_DEPTH) {
}
Chunk::~Chunk() {}

static const int neighborOffsets[6][3] = {
	{ 0,  0,  1},  // Front
	{ 0,  0, -1},  // Back
	{ 1,  0,  0},  // Right
	{-1,  0,  0},  // Left
	{ 0,  1,  0},  // Top
	{ 0, -1,  0}   // Bottom
};

bool isRemoved(int x, int y, int z) {
	while (x > 0 || y > 0 || z > 0) {
		if (x % 3 == 1 && y % 3 == 1 ||
			x % 3 == 1 && z % 3 == 1 ||
			y % 3 == 1 && z % 3 == 1) {
			return true;
		}
		x /= 3;
		y /= 3;
		z /= 3;
	}
	return false;
}

//--------------------------------------------------------------------
// Temporary Generation Code
//--------------------------------------------------------------------
// This method currently creates a simple pattern:
// it fills the entire chunk with air (0) and sets the lower half (in Y) to a solid block type (1).
// Will be replaced later in a WorldGenerator class.
void Chunk::GenerateData()
{
	_data.Fill(0);

	for (size_t z = 0; z < CHUNK_DEPTH; ++z)
	{
		for (size_t y = 0; y < CHUNK_HEIGHT; ++y)
		{
			for (size_t x = 0; x < CHUNK_WIDTH; ++x)
			{
				/*
				if (y < CHUNK_HEIGHT / 2)
				{
					_data.At(x, y, z) = 1;
				}
				*/

				if (!isRemoved(x, y, z))
				{
					_data.At(x, y, z) = 1;
				}
			}
		}
	}
}

Mesh Chunk::GenerateMesh() const
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int vertexIndex = 0;

	// Front face (facing +Z)
	static const float frontFace[32] = {
		// Position              // Color         // TexCoords
		-0.5f, -0.5f,  0.5f,      1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // v0: bottom-left
		 0.5f, -0.5f,  0.5f,      1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // v1: bottom-right
		 0.5f,  0.5f,  0.5f,      1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // v2: top-right
		-0.5f,  0.5f,  0.5f,      1.0f, 0.0f, 0.0f,   0.0f, 1.0f   // v3: top-left
	};

	// Back face (facing -Z)
	static const float backFace[32] = {
		 0.5f, -0.5f, -0.5f,      0.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // v0: bottom-left
		-0.5f, -0.5f, -0.5f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // v1: bottom-right
		-0.5f,  0.5f, -0.5f,      0.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // v2: top-right
		 0.5f,  0.5f, -0.5f,      0.0f, 1.0f, 0.0f,   0.0f, 1.0f   // v3: top-left
	};

	// Right face (facing +X)
	static const float rightFace[32] = {
		 0.5f, -0.5f,  0.5f,      0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // v0: bottom-left
		 0.5f, -0.5f, -0.5f,      0.0f, 0.0f, 1.0f,   1.0f, 0.0f,  // v1: bottom-right
		 0.5f,  0.5f, -0.5f,      0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  // v2: top-right
		 0.5f,  0.5f,  0.5f,      0.0f, 0.0f, 1.0f,   0.0f, 1.0f   // v3: top-left
	};

	// Left face (facing -X)
	static const float leftFace[32] = {
		-0.5f, -0.5f, -0.5f,      1.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // v0: bottom-left
		-0.5f, -0.5f,  0.5f,      1.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // v1: bottom-right
		-0.5f,  0.5f,  0.5f,      1.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // v2: top-right
		-0.5f,  0.5f, -0.5f,      1.0f, 1.0f, 0.0f,   0.0f, 1.0f   // v3: top-left
	};

	// Top face (facing +Y)
	static const float topFace[32] = {
		-0.5f,  0.5f,  0.5f,      1.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // v0: bottom-left
		 0.5f,  0.5f,  0.5f,      1.0f, 0.0f, 1.0f,   1.0f, 0.0f,  // v1: bottom-right
		 0.5f,  0.5f, -0.5f,      1.0f, 0.0f, 1.0f,   1.0f, 1.0f,  // v2: top-right
		-0.5f,  0.5f, -0.5f,      1.0f, 0.0f, 1.0f,   0.0f, 1.0f   // v3: top-left
	};

	// Bottom face (facing -Y)
	static const float bottomFace[32] = {
		 0.5f, -0.5f,  0.5f,      0.0f, 1.0f, 1.0f,   1.0f, 0.0f,  // v0: bottom-left
		-0.5f, -0.5f,  0.5f,      0.0f, 1.0f, 1.0f,   0.0f, 0.0f,  // v1: bottom-right
		-0.5f, -0.5f, -0.5f,      0.0f, 1.0f, 1.0f,   0.0f, 1.0f,  // v2: top-right
		 0.5f, -0.5f, -0.5f,      0.0f, 1.0f, 1.0f,   1.0f, 1.0f   // v3: top-left
	};

	static const float* faceData[6] = {
		frontFace, backFace, rightFace, leftFace, topFace, bottomFace
	};

	static const unsigned int localIndices[6] = { 0, 1, 2, 0, 2, 3 };

	auto isFaceExposed = [this](int x, int y, int z) -> bool
		{
			if (x < 0 || x >= static_cast<int>(CHUNK_WIDTH) ||
				y < 0 || y >= static_cast<int>(CHUNK_HEIGHT) ||
				z < 0 || z >= static_cast<int>(CHUNK_DEPTH))
			{
				return true;
			}

			return (_data.At(static_cast<size_t>(x), static_cast<size_t>(y), static_cast<size_t>(z)) == 0);
		};

	// Prepare Mesh
	for (size_t z = 0; z < CHUNK_DEPTH; ++z)
	{
		for (size_t y = 0; y < CHUNK_HEIGHT; ++y)
		{
			for (size_t x = 0; x < CHUNK_WIDTH; ++x)
			{
				unsigned short blockType = _data.At(x, y, z);
				if (blockType == 0)
				{
					continue;
				}

				for (int face = 0; face < 6; ++face)
				{
					int nx = static_cast<int>(x) + neighborOffsets[face][0];
					int ny = static_cast<int>(y) + neighborOffsets[face][1];
					int nz = static_cast<int>(z) + neighborOffsets[face][2];

					if (!isFaceExposed(nx, ny, nz))
					{
						continue;
					}

					for (int v = 0; v < 4; ++v)
					{
						int baseIndex = v * 8;

						float posX = static_cast<float>(x) + 0.5f + faceData[face][baseIndex + 0];
						float posY = static_cast<float>(y) + 0.5f + faceData[face][baseIndex + 1];
						float posZ = static_cast<float>(z) + 0.5f + faceData[face][baseIndex + 2];
						vertices.push_back(posX);
						vertices.push_back(posY);
						vertices.push_back(posZ);

						vertices.push_back(faceData[face][baseIndex + 3]);
						vertices.push_back(faceData[face][baseIndex + 4]);
						vertices.push_back(faceData[face][baseIndex + 5]);

						vertices.push_back(faceData[face][baseIndex + 6]);
						vertices.push_back(faceData[face][baseIndex + 7]);
					}

					for (int i = 0; i < 6; ++i)
					{
						indices.push_back(vertexIndex + localIndices[i]);
					}

					vertexIndex += 4;
				}
			}
		}
	}

	return Mesh(vertices, indices);
}

const MultiDimArray& Chunk::GetData() const
{
	return _data;
}