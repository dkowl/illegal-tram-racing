#pragma once
#include <memory>

#include "../glbinding.h"

#include "ShaderResource.h"
#include "ShaderId.h"
#include "Mesh/Mesh.h"
#include "Mesh/MeshId.h"

class Resources
{
	std::unique_ptr<ShaderResource> shaders[int(ShaderId::COUNT)];
	unsigned int shaderProgram;

	std::unique_ptr<Mesh> meshes[int(MeshId::COUNT)];
public:
	Resources();

	const std::unique_ptr<ShaderResource>& GetShader(ShaderId id) const;
	const int& ShaderProgram() const;
	const std::unique_ptr<Mesh>& GetMesh(MeshId id) const;

private:
	void LoadShaders();
	void LoadMeshes();
};

