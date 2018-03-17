#pragma once

#include "../../glbinding.h"

#include "ShaderSource.h"
#include "ShaderSourceId.h"

class ShaderProgram
{
	ShaderSourceId vertexShader;
	ShaderSourceId fragmentShader;

	unsigned int glId;

public:
	ShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

	const unsigned int& GlId() const;

};
