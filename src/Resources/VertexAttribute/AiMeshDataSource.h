#pragma once

class AiMeshDataSource
{
public:
	enum class Type;

private:
	Type type;
	unsigned id;

public:
	AiMeshDataSource(const Type &type, const unsigned &id = 0); 
	
	enum class Type {
		BITANGETNTS,
		COLORS,
		NORMALS,
		TANGENTS,
		UVS,
		POSITIONS
	};
};

inline AiMeshDataSource::AiMeshDataSource(const Type &type, const unsigned &id) :
	type(type),
	id(id)
{

}
