#include "AiMeshDataSource.h"

AiMeshDataSource::AiMeshDataSource(const Type &type, const unsigned &id) :
	type(type),
	id(id)
{

}

aiVector3D* AiMeshDataSource::GetVectors3D(aiMesh* aiMesh) const
{
	switch (type)
	{
	case Type::NORMALS:
		return aiMesh->mNormals;
	case Type::COLORS:
		return nullptr;
	case Type::UVS:
		return aiMesh->mTextureCoords[id];
	case Type::POSITIONS:
		return aiMesh->mVertices;
	case Type::BITANGENTS:
		return aiMesh->mBitangents;
	case Type::TANGENTS:
		return aiMesh->mTangents;
	default:
		return nullptr;
	}
}