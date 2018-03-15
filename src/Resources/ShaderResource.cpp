#include "ShaderResource.h"

ShaderResource::ShaderResource(const std::string &filename)
{
	auto file = std::ifstream(SHADER_RESOURCE_PATH + filename);
	
	assert(file.good());

	std::stringstream buffer;
	buffer << file.rdbuf();
	source = buffer.str();

}

const std::string& ShaderResource::Source() const
{
	return source;
}

const std::string ShaderResource::SHADER_RESOURCE_PATH = Constants::RESOURCE_PATH + "Shaders/";
