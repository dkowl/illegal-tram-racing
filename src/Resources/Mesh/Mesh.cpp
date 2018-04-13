#include "Mesh.h"

#include <iostream>
#include <assimp/postprocess.h>

#include "../../glbinding.h"

#include "../../Game/Track.h"
#include "../MeshLayout/MeshLayout.h"

Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned>& triangles) :
	vertCount(vertices.size() / 3)
{
	arrayBufferData = std::move(vertices);
	elementBufferData = std::move(triangles);

	GenerateGlBuffers();
}

Mesh::Mesh(std::vector<float> &vertices, std::vector<unsigned> &triangles, std::vector<float> &uvs):
	vertCount(vertices.size() / 3),
	arrayBufferData(vertCount * 5)
{
	elementBufferData = std::move(triangles);

	for (int i = 0; i < vertCount; i++)
	{
		arrayBufferData[i * 5] = vertices[i * 3];
		arrayBufferData[i * 5 + 1] = vertices[i * 3 + 1];
		arrayBufferData[i * 5 + 2] = vertices[i * 3 + 2];
		arrayBufferData[i * 5 + 3] = uvs[i * 2];
		arrayBufferData[i * 5 + 4] = uvs[i * 2 + 1];
	}
}

Mesh::Mesh(aiMesh* aiMesh):
	vertCount(aiMesh->mNumVertices),
	arrayBufferData(vertCount * 5),
	elementBufferData(aiMesh->mNumFaces * 3)
{
	const auto vertices = aiMesh->mVertices;
	const auto uvs = aiMesh->mTextureCoords[0];
	for (unsigned int i = 0; i < vertCount; i++)
	{
		arrayBufferData[i * 5] = vertices[i].x;
		arrayBufferData[i * 5 + 1] = vertices[i].y;
		arrayBufferData[i * 5 + 2] = vertices[i].z;
		arrayBufferData[i * 5 + 3] = uvs[i].x;
		arrayBufferData[i * 5 + 4] = uvs[i].y;
	}

	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
	{
		elementBufferData[i * 3] = aiMesh->mFaces[i].mIndices[0];
		elementBufferData[i * 3 + 1] = aiMesh->mFaces[i].mIndices[1];
		elementBufferData[i * 3 + 2] = aiMesh->mFaces[i].mIndices[2];
	}

	GenerateGlBuffers();
}

Mesh::Mesh(const Track& track):
	vertCount(track.SegmentCount() * 3),
	arrayBufferData(vertCount * 5),
	elementBufferData((track.SegmentCount() - 1) * 12)
{
	for (int i = 0; i < track.SegmentCount(); i++)
	{
		auto positions = track.SegmentVertexPositions(i);
		auto uvs = track.SegmentVertexUvs(i);
		
		if(i<5)
		{
			std::cout << "\nSegment " << i << std::endl;
			std::cout << "positions:\n";
			for(auto&& position: positions)
			{
				Utils::DisplayVec3(position);
			}
			std::cout << "uvs:\n";
			for(auto&& uv: uvs)
			{
				std::cout << uv.x << ", " << uv.y << "\n";
			}
		}

		for (int j = 0; j < 3; j++)
		{
			AddSingleVertexData(i * 3 + j, positions[j], uvs[j]);
		}
		if(i > 0)
		{
			elementBufferData[(i - 1) * 12] = (i - 1) * 3;
			elementBufferData[(i - 1) * 12 + 1] = (i - 1) * 3 + 1;
			elementBufferData[(i - 1) * 12 + 2] = i * 3 + 1;

			elementBufferData[(i - 1) * 12 + 3] = (i - 1) * 3;
			elementBufferData[(i - 1) * 12 + 4] = i * 3 + 1;
			elementBufferData[(i - 1) * 12 + 5] = i * 3;

			elementBufferData[(i - 1) * 12 + 6] = (i - 1) * 3 + 1;
			elementBufferData[(i - 1) * 12 + 7] = (i - 1) * 3 + 2;
			elementBufferData[(i - 1) * 12 + 8] = i * 3 + 2;

			elementBufferData[(i - 1) * 12 + 9] = (i - 1) * 3 + 1;
			elementBufferData[(i - 1) * 12 + 10] = i * 3 + 1;
			elementBufferData[(i - 1) * 12 + 11] = i * 3 + 2;
		}
	}

	GenerateGlBuffers();
}

Mesh::Mesh(aiMesh* aiMesh, MeshLayout layout)
{
}


const unsigned& Mesh::Vao() const
{
	return vao;
}

const unsigned& Mesh::ElementCount() const
{
	return elementBufferData.size();
}

void Mesh::AddSingleVertexData(const int &vertexId, const glm::vec3 &position, const glm::vec2 &uv)
{
	arrayBufferData[vertexId * 5] = position.x;
	arrayBufferData[vertexId * 5 + 1] = position.y;
	arrayBufferData[vertexId * 5 + 2] = position.z;
	arrayBufferData[vertexId * 5 + 3] = uv.x;
	arrayBufferData[vertexId * 5 + 4] = uv.y;
}

void Mesh::GenerateGlBuffers()
{
	gl::glGenVertexArrays(1, &vao);
	gl::glGenBuffers(1, &vbo);
	gl::glGenBuffers(1, &ebo);

	gl::glBindVertexArray(vao);

	gl::glBindBuffer(gl::GLenum::GL_ARRAY_BUFFER, vbo);
	gl::glBufferData(gl::GLenum::GL_ARRAY_BUFFER, arrayBufferData.size() * sizeof(float), arrayBufferData.data(), gl::GLenum::GL_STATIC_DRAW);

	gl::glBindBuffer(gl::GLenum::GL_ELEMENT_ARRAY_BUFFER, ebo);
	gl::glBufferData(gl::GLenum::GL_ELEMENT_ARRAY_BUFFER, elementBufferData.size() * sizeof(unsigned), elementBufferData.data(), gl::GLenum::GL_STATIC_DRAW);

	//position attribute
	gl::glVertexAttribPointer(0, 3, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 5 * sizeof(float), nullptr);
	gl::glEnableVertexAttribArray(0);

	//uv attribute
	gl::glVertexAttribPointer(1, 2, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	gl::glEnableVertexAttribArray(1);
}
