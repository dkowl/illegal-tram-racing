#include "Resources.h"

Resources::Resources()
{
	LoadShaders();
}

const std::unique_ptr<ShaderResource>& Resources::GetShader(ShaderId id) const
{
	return shaders[int(id)];
}

const int& Resources::ShaderProgram() const
{
	return shaderProgram;
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

