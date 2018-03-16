#include "Resources.h"

Resources::Resources()
{
}

void Resources::Initialize()
{
	LoadShaders();
	LoadMeshes();
}

const std::unique_ptr<ShaderResource>& Resources::GetShader(ShaderId id) const
{
	return shaders[int(id)];
}

const int& Resources::ShaderProgram() const
{
	return shaderProgram;
}

const std::unique_ptr<Mesh>& Resources::GetMesh(MeshId id) const
{
	return meshes[int(id)];
}

void Resources::LoadShaders()
{
	shaders[int(ShaderId::MAIN_VERTEX)] = std::make_unique<ShaderResource>("vertex_shader.glsl", gl::GLenum::GL_VERTEX_SHADER);
	shaders[int(ShaderId::MAIN_FRAGMENT)] = std::make_unique<ShaderResource>("fragment_shader.glsl", gl::GLenum::GL_FRAGMENT_SHADER);

	shaderProgram = gl::glCreateProgram();
	gl::glAttachShader(shaderProgram, GetShader(ShaderId::MAIN_VERTEX)->GlId());
	gl::glAttachShader(shaderProgram, GetShader(ShaderId::MAIN_FRAGMENT)->GlId());
	gl::glLinkProgram(shaderProgram);

	int success;
	glGetProgramiv(shaderProgram, gl::GLenum::GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		gl::glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	else std::cout << "Shader program linked successfully\n";
}

void Resources::LoadMeshes()
{
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.5f, //0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, //1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, //0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, //0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, //1.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, //0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, //1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, //1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, //0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, //0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, //1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, //1.0f, 0.0f,

		0.5f, -0.5f, -0.5f, //0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, //0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, //1.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, //0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, //0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, //1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, //1.0f, 0.0f
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

