#pragma once
#include "AiMeshDataSource.h"

class VertexAttribute
{

	unsigned size;
	AiMeshDataSource aiMeshDataSource;

public:
	VertexAttribute(unsigned size, AiMeshDataSource aiMeshDataSource);
	unsigned Size() const;
	AiMeshDataSource DataSource() const;

	static const VertexAttribute 
		POSITION, 
		NORMAL, 
		UV, 
		UV1, 
		UV2, 
		UV3, 
		COLOR;
};
