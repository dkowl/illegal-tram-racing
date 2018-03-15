#include "Resources.h"

Resources::Resources()
{
	LoadShaders();
}

const std::unique_ptr<ShaderResource>& Resources::GetShader(ShaderId id) const
{
	return shaders[int(id)];
}

void Resources::LoadShaders()
{
	shaders[int(ShaderId::MAIN_VERTEX)] = std::make_unique<ShaderResource>("vertex_shader.glsl", gl::GLenum::GL_VERTEX_SHADER);
	shaders[int(ShaderId::MAIN_FRAGMENT)] = std::make_unique<ShaderResource>("fragment_shader.glsl", gl::GLenum::GL_FRAGMENT_SHADER);
}

