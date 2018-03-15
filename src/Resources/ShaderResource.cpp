#include "ShaderResource.h"

ShaderResource::ShaderResource(const std::string &filename, gl::GLenum type)
{
	auto file = std::ifstream(SHADER_RESOURCE_PATH + filename);
	
	assert(file.good());

	std::stringstream buffer;
	buffer << file.rdbuf();

	source = buffer.str();
	glType = type;
	glId = gl::glCreateShader(type);
	const char* sourceCstr = source.c_str();
	gl::glShaderSource(glId, 1, &sourceCstr, nullptr);
	gl::glCompileShader(glId);

	int success;
	char infoLog[512];
	gl::glGetShaderiv(glId, gl::GLenum::GL_COMPILE_STATUS, &success);
	if (!success)
	{
		gl::glGetShaderInfoLog(glId, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::" << filename <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else std::cout << "Shader " << filename << " compiled successfully" << std::endl;
}

const std::string& ShaderResource::Source() const
{
	return source;
}

const unsigned& ShaderResource::GlId() const
{
	return glId;
}

const std::string ShaderResource::SHADER_RESOURCE_PATH = Constants::RESOURCE_PATH + "Shaders/";
