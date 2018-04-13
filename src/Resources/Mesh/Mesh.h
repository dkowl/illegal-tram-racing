#pragma once
#include <vector>
#include <assimp/scene.h>
#include <glm/detail/type_vec3.hpp>

class Track;
class MeshLayout;

class Mesh
{
	unsigned int vertCount;

	std::vector<float> arrayBufferData;
	std::vector<unsigned int> elementBufferData;

	unsigned int vbo;
	unsigned int ebo;
	unsigned int vao;

public:
	Mesh(std::vector<float> &vertices, std::vector<unsigned int> &triangles);
	Mesh(std::vector<float> &vertices, std::vector<unsigned int> &triangles, std::vector<float> &uvs);
	explicit Mesh(aiMesh *aiMesh);
	explicit Mesh(const Track &track);
	Mesh(aiMesh *aiMesh, const MeshLayout &layout);

	const unsigned& Vao() const;
	const unsigned& ElementCount() const;

private:
	void AddSingleVertexData(const int &vertexId, const glm::vec3 &position, const glm::vec2 &uv);

	void GenerateGlBuffers();
};
