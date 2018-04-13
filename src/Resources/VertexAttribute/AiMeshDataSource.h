#pragma once
#include <assimp/scene.h>

class AiMeshDataSource
{
public:
	enum class Type;

private:
	Type type;
	unsigned id;

public:
	AiMeshDataSource(const Type &type, const unsigned &id = 0); 

	aiVector3D* GetVectors3D(aiMesh* aiMesh) const;
	
	enum class Type {
		COLORS,
		NORMALS,
		TANGENTS,
		BITANGENTS,
		UVS,
		POSITIONS
	};
};
