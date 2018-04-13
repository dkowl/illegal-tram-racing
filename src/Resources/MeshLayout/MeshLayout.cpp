#include "MeshLayout.h"

MeshLayout::MeshLayout(std::initializer_list<const VertexAttribute> initList)
{
	attributes.reserve(initList.size());
	for (auto&& i : initList)
	{
		attributes.push_back(std::ref(i));
	}
}
