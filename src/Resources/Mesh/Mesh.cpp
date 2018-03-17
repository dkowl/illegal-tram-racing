#include "Mesh.h"

Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned>& triangles) :
	vertCount(vertices.size() / 3)
{
	arrayBufferData = std::move(vertices);
	elementBufferData = std::move(triangles);

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

const unsigned& Mesh::Vao() const
{
	return vao;
}

const unsigned& Mesh::ElementCount() const
{
	return elementBufferData.size();
}
