// MultiDimArray.h

#ifndef MULTI_DIM_ARRAY_H
#define MULTI_DIM_ARRAY_H

#include <vector>
#include <cstddef>

class MultiDimArray
{
public:
	MultiDimArray(size_t width, size_t height, size_t depth);
	~MultiDimArray();

	MultiDimArray(const MultiDimArray& other);
	MultiDimArray& operator=(const MultiDimArray& other);

	MultiDimArray(MultiDimArray&& other) noexcept;
	MultiDimArray& operator=(MultiDimArray&& other) noexcept;

	size_t GetWidth() const;
	size_t GetHeight() const;
	size_t GetDepth() const;

	unsigned short& At(size_t x, size_t y, size_t z);
	const unsigned short& At(size_t x, size_t y, size_t z) const;

	unsigned short& operator()(size_t x, size_t y, size_t z);
	const unsigned short& operator()(size_t x, size_t y, size_t z) const;

	void Fill(unsigned short value);

private:
	size_t _width;
	size_t _height;
	size_t _depth;

	std::vector<unsigned short> _data;

	size_t Index(size_t x, size_t y, size_t z) const;
};

#endif