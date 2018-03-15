#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

#include "../Constants.h"

class ShaderResource
{
	static const std::string SHADER_RESOURCE_PATH;

	std::string source;

public:
	ShaderResource(const std::string &filename);

	const std::string& Source() const;
};

