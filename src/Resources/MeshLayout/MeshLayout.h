#pragma once
#include <vector>
#include "../VertexAttribute/VertexAttribute.h"

class MeshLayout
{
public:
	typedef std::vector<VertexAttribute::Values> AttributeValues;

	std::vector<VertexAttribute> attributes;
	size_t stride;
	unsigned int size;

public:
	MeshLayout(std::initializer_list<VertexAttribute> initList);

	size_t Stride() const;
	unsigned int Size() const;
	unsigned int AttributeCount() const;
	const VertexAttribute& Attribute(unsigned id) const;
	AttributeValues AllValues(aiMesh* aiMesh) const;

private:
	void CalculateStrideAndSize();

};
