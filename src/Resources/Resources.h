#pragma once
#include <memory>

#include "../glbinding.h"

#include "ShaderResource.h"
#include "ShaderId.h"

class Resources
{
	std::unique_ptr<ShaderResource> shaders[int(ShaderId::COUNT)];
public:
	Resources();

	const std::unique_ptr<ShaderResource>& GetShader(ShaderId id) const;

private:
	void LoadShaders();
};
