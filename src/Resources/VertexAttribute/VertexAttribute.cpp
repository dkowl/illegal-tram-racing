#include "VertexAttribute.h"

const VertexAttribute VertexAttribute::POSITION(3, AiMeshDataSource(AiMeshDataSource::Type::POSITIONS));
const VertexAttribute VertexAttribute::NORMAL(3, AiMeshDataSource(AiMeshDataSource::Type::NORMALS));
const VertexAttribute VertexAttribute::UV(3, AiMeshDataSource(AiMeshDataSource::Type::UVS));
const VertexAttribute VertexAttribute::UV1(3, AiMeshDataSource(AiMeshDataSource::Type::UVS, 1));
const VertexAttribute VertexAttribute::UV2(3, AiMeshDataSource(AiMeshDataSource::Type::UVS, 2));
const VertexAttribute VertexAttribute::UV3(3, AiMeshDataSource(AiMeshDataSource::Type::UVS, 3));
const VertexAttribute VertexAttribute::COLOR(3, AiMeshDataSource(AiMeshDataSource::Type::COLORS));

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
