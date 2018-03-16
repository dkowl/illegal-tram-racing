#pragma once
#include <vector>

#include "../../glbinding.h"

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

	const unsigned& Vao() const;
};
