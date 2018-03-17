#include "Resources.h"

Resources::Resources()
{
}

void Resources::Initialize()
{
	CompileShaders();
	LinkShaderPrograms();
	LoadMeshes();
	LoadTextures();
}

const std::unique_ptr<ShaderSource>& Resources::GetShaderSource(ShaderSourceId id) const
{
	return shaderSources[int(id)];
}

const std::unique_ptr<ShaderProgram>& Resources::GetShaderProgram(ShaderProgramId id) const
{
	return shaderPrograms[int(id)];
}

const std::unique_ptr<Mesh>& Resources::GetMesh(MeshId id) const
{
	return meshes[int(id)];
}

const std::unique_ptr<Texture>& Resources::GetTexture(TextureId id) const
{
	return textures[int(id)];
}

void Resources::CompileShaders()
{
	shaderSources[int(ShaderSourceId::MAIN_VERTEX)] = std::make_unique<ShaderSource>("vertex_shader.glsl", gl::GLenum::GL_VERTEX_SHADER);
	shaderSources[int(ShaderSourceId::MAIN_FRAGMENT)] = std::make_unique<ShaderSource>("fragment_shader.glsl", gl::GLenum::GL_FRAGMENT_SHADER);
}

void Resources::LinkShaderPrograms()
{
	shaderPrograms[int(ShaderProgramId::MAIN)] = std::make_unique<ShaderProgram>(
		GetShaderSource(ShaderSourceId::MAIN_VERTEX)->GlId(),
		GetShaderSource(ShaderSourceId::MAIN_FRAGMENT)->GlId()
		);
}

void Resources::LoadMeshes()
{
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,

		0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	};

	meshes[int(MeshId::CUBE)] = std::make_unique<Mesh>(vertices, indices);
}

void Resources::LoadTextures()
{
	textures[int(TextureId::CRATE)] = std::make_unique<Texture>("crate.jpg");
}

