#include "MeshLayout.h"

MeshLayout::MeshLayout(std::initializer_list<const VertexAttribute> initList)
{
	attributes.reserve(initList.size());
	for (auto&& i : initList)
	{
		attributes.push_back(std::ref(i));
	}
}

const MeshLayout MeshLayout::SIMPLE_TEXTURED{ VertexAttribute::POSITION, VertexAttribute::UV };

//TODO: to avoid static initialization order fiasco we will move the static const instances to Resources
