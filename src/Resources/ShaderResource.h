#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>

#include "../glbinding.h"

#include "../Constants.h"

class ShaderResource
{
	static const std::string SHADER_RESOURCE_PATH;

	std::string source;
	unsigned int glId;
	gl::GLenum glType;

public:
	ShaderResource(const std::string &filename, gl::GLenum type);

	const std::string& Source() const;
	const unsigned int& GlId() const;
};

