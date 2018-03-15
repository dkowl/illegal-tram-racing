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
	shaders[int(ShaderId::MAIN_VERTEX_SHADER)] = std::make_unique<ShaderResource>("vertex_shader.glsl");
}

