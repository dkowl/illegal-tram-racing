#pragma once
#include <vector>
#include <functional>
#include "../VertexAttribute/VertexAttribute.h"

class MeshLayout
{
	std::vector<std::reference_wrapper<const VertexAttribute>> attributes;
	size_t stride;

public:
	MeshLayout(std::initializer_list<const VertexAttribute> initList);

	size_t Stride() const;

private:
	void CalculateStride();

};
