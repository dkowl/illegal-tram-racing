#include "MeshLayout.h"

MeshLayout::MeshLayout(std::initializer_list<const VertexAttribute> initList)
{
	attributes.reserve(initList.size());
	for (auto&& i : initList)
	{
		attributes.push_back(std::ref(i));
	}
	CalculateStride();
}

size_t MeshLayout::Stride() const
{
	return stride;
}

void MeshLayout::CalculateStride()
{
	stride = 0;
	for(auto&& i : attributes)
	{
		stride += i.get().Size();
	}
}
