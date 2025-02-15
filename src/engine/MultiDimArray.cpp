// MultiDimArray.cpp

#include "MultiDimArray.h"

#include <stdexcept>
#include <algorithm>

MultiDimArray::MultiDimArray(size_t width, size_t height, size_t depth)
	: _width(width), _height(height), _depth(depth), _data(width * height * depth, 0) {}
MultiDimArray::~MultiDimArray() {}

MultiDimArray::MultiDimArray(const MultiDimArray& other)
	: _width(other._width), _height(other._height), _depth(other._depth), _data(other._data) {}

MultiDimArray& MultiDimArray::operator=(const MultiDimArray& other)
{
	if (this == &other)
	{
		return *this;
	}

	_width = other._width;
	_height = other._height;
	_depth = other._depth;
	_data = other._data;

	return *this;
}

MultiDimArray::MultiDimArray(MultiDimArray&& other) noexcept
	: _width(other._width), _height(other._height), _depth(other._depth), _data(std::move(other._data))
{
	other._width = 0;
	other._height = 0;
	other._depth = 0;
}

MultiDimArray& MultiDimArray::operator=(MultiDimArray&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	_width = other._width;
	_height = other._height;
	_depth = other._depth;

	_data = std::move(other._data);

	other._width = 0;
	other._height = 0;
	other._depth = 0;

	return *this;
}

size_t MultiDimArray::GetWidth() const
{
	return _width;
}

size_t MultiDimArray::GetHeight() const
{
	return _height;
}

size_t MultiDimArray::GetDepth() const
{
	return _depth;
}

size_t MultiDimArray::Index(size_t x, size_t y, size_t z) const
{
	// Check bounds
	if (x >= _width || y >= _height || z >= _depth)
	{
		throw std::out_of_range("MultiDimArray: Index out of range!");
	}

	// 1D array conversion into 3D coords
	return x + y * _width + z * _width * _height;
}

unsigned short& MultiDimArray::At(size_t x, size_t y, size_t z)
{
	return _data[Index(x, y, z)];
}

const unsigned short& MultiDimArray::At(size_t x, size_t y, size_t z) const
{
	return _data[Index(x, y, z)];
}

unsigned short& MultiDimArray::operator()(size_t x, size_t y, size_t z)
{
	return At(x, y, z);
}

const unsigned short& MultiDimArray::operator()(size_t x, size_t y, size_t z) const
{
	return At(x, y, z);
}

void MultiDimArray::Fill(unsigned short value) {
	std::fill(_data.begin(), _data.end(), value);
}