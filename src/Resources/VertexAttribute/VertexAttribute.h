#pragma once
#include <vector>
#include <assimp/scene.h>
#include "AiMeshDataSource.h"

class VertexAttribute
{
public:
	typedef std::vector<std::vector<float>> Values;

private:
	unsigned size;
	AiMeshDataSource aiMeshDataSource;

public:
	VertexAttribute(unsigned size, AiMeshDataSource aiMeshDataSource);
	unsigned Size() const;
	AiMeshDataSource DataSource() const;

	Values GetValues(aiMesh* aiMesh) const;

	static const VertexAttribute 
		POSITION, 
		NORMAL, 
		TANGENT,
		BITANGENT,
		UV, 
		UV1, 
		UV2, 
		UV3, 
		COLOR;
};
