#include "Mesh.h"

#include <iostream>
#include <assimp/postprocess.h>

#include "../../glbinding.h"

#include "../../Game/Track.h"
#include "../MeshLayout/MeshLayout.h"
#include "../../Game/Game.h"

Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned>& triangles) :
	layout(*Game::Resources().Get(MeshLayoutId::SIMPLE_TEXTURED)),
	vertCount(vertices.size() / 3)
{
	arrayBufferData = std::move(vertices);
	elementBufferData = std::move(triangles);

	GenerateGlBuffers();
}

Mesh::Mesh(const Track& track):
	layout(*Game::Resources().Get(MeshLayoutId::SIMPLE_TEXTURED)),
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

Mesh::Mesh(aiMesh* aiMesh, const MeshLayout &layout):
	layout(layout),
	vertCount(aiMesh->mNumVertices),
	arrayBufferData(vertCount * layout.Size()),
	elementBufferData(aiMesh->mNumFaces * 3)
{
	auto allValues = layout.AllValues(aiMesh);

	for (int vertId = 0; vertId < vertCount; vertId++)
	{
		int currentIndexOffset = 0;
		for (int attrId = 0; attrId < layout.AttributeCount(); attrId++)
		{
			for (int valueId = 0; valueId < layout.Attribute(attrId).Size(); valueId++)
			{
				arrayBufferData[vertId * layout.Size() + currentIndexOffset] = allValues[attrId][vertId][valueId];
				currentIndexOffset++;
			}
		}
	}

	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
	{
		elementBufferData[i * 3] = aiMesh->mFaces[i].mIndices[0];
		elementBufferData[i * 3 + 1] = aiMesh->mFaces[i].mIndices[1];
		elementBufferData[i * 3 + 2] = aiMesh->mFaces[i].mIndices[2];
	}

	GenerateGlBuffers();
}


const unsigned& Mesh::Vao() const
{
	return vao;
}

unsigned Mesh::ElementCount() const
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

	for (int attrId = 0; attrId < layout.AttributeCount(); attrId++)
	{
		gl::glVertexAttribPointer(attrId, layout.Attribute(attrId).Size(), gl::GLenum::GL_FLOAT, gl::GL_FALSE, layout.Stride(), layout.AttributeOffset(attrId));
		gl::glEnableVertexAttribArray(attrId);
	}
}
