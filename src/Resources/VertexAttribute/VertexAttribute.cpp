#include "VertexAttribute.h"
#include "../../Game/Game.h"


const VertexAttribute VertexAttribute::POSITION(3, AiMeshDataSource(AiMeshDataSource::Type::POSITIONS));
const VertexAttribute VertexAttribute::NORMAL(3, AiMeshDataSource(AiMeshDataSource::Type::NORMALS));
const VertexAttribute VertexAttribute::TANGENT(3, AiMeshDataSource(AiMeshDataSource::Type::TANGENTS));
const VertexAttribute VertexAttribute::BITANGENT(3, AiMeshDataSource(AiMeshDataSource::Type::BITANGENTS));
const VertexAttribute VertexAttribute::UV(2, AiMeshDataSource(AiMeshDataSource::Type::UVS));
const VertexAttribute VertexAttribute::UV1(2, AiMeshDataSource(AiMeshDataSource::Type::UVS, 1));
const VertexAttribute VertexAttribute::UV2(2, AiMeshDataSource(AiMeshDataSource::Type::UVS, 2));
const VertexAttribute VertexAttribute::UV3(2, AiMeshDataSource(AiMeshDataSource::Type::UVS, 3));
const VertexAttribute VertexAttribute::COLOR(4, AiMeshDataSource(AiMeshDataSource::Type::COLORS));

VertexAttribute::VertexAttribute(unsigned size, AiMeshDataSource aiMeshDataSource):
size(size),
aiMeshDataSource(aiMeshDataSource)
{
}

unsigned VertexAttribute::Size() const
{
	return size;
}

AiMeshDataSource VertexAttribute::DataSource() const
{
	return aiMeshDataSource;
}

std::vector<std::vector<float>> VertexAttribute::GetValues(aiMesh* aiMesh) const
{
	std::vector<std::vector<float>> result;
	result.reserve(aiMesh->mNumVertices);

	aiVector3D* vectors3D = aiMeshDataSource.GetVectors3D(aiMesh);
	if(vectors3D != nullptr)
	{
		for (int i = 0; i < aiMesh->mNumVertices; i++) {
			switch (size)
			{
			case 2:
				result.push_back({ vectors3D[i].x, vectors3D[i].y });
				break;
			case 3:
				result.push_back({ vectors3D[i].x, vectors3D[i].y, vectors3D[i].z });
				break;
			default:
				Game::LogError("Invalid VertexAttribute size");
			}
		}
	}
	if (result.empty()) Game::LogError("Cannot find VertexAttribute values");
	return result;
}
