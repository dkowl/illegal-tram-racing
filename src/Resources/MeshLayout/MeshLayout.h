#pragma once
#include <vector>
#include <functional>
#include "../VertexAttribute/VertexAttribute.h"

class MeshLayout
{
	std::vector<std::reference_wrapper<const VertexAttribute>> attributes;

public:
	MeshLayout(std::initializer_list<const VertexAttribute> initList);

	static const MeshLayout SIMPLE_TEXTURED;

};
