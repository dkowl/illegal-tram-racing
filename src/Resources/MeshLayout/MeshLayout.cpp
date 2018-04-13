#include "MeshLayout.h"

MeshLayout::MeshLayout(std::initializer_list<VertexAttribute> initList)
{
	attributes.reserve(initList.size());
	for (auto&& i : initList)
	{
		attributes.push_back(i);
	}
	CalculateStrideAndSize();
}

size_t MeshLayout::Stride() const
{
	return stride;
}

unsigned MeshLayout::Size() const
{
	return size;
}

unsigned MeshLayout::AttributeCount() const
{
	return attributes.size();
}

const VertexAttribute& MeshLayout::Attribute(unsigned id) const
{
	return attributes[id];
}

void* MeshLayout::AttributeOffset(unsigned id) const
{
	return offsets[id];
}

MeshLayout::AttributeValues MeshLayout::AllValues(aiMesh* aiMesh) const
{
	AttributeValues result;
	result.reserve(AttributeCount());

	for(auto&& i : attributes)
	{
		result.push_back(i.GetValues(aiMesh));
	}

	return result;
}

void MeshLayout::CalculateStrideAndSize()
{
	stride = 0;
	size = 0;
	for(auto&& i : attributes)
	{
		offsets.push_back(reinterpret_cast<void*>(stride));
		stride += i.Size() * sizeof(float);
		size += i.Size();
	}
}
