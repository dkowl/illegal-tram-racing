#pragma once
#include <memory>

#include "../glbinding.h"

#include "ShaderResource.h"
#include "ShaderId.h"
#include "Mesh/Mesh.h"
#include "Mesh/MeshId.h"
#include "Texture/Texture.h"
#include "Texture/TextureId.h"

class Resources
{
	std::unique_ptr<ShaderResource> shaders[int(ShaderId::COUNT)];
	unsigned int shaderProgram;

	std::unique_ptr<Mesh> meshes[int(MeshId::COUNT)];
	std::unique_ptr<Texture> textures[int(TextureId::COUNT)];
public:
	Resources();
	void Initialize();

	const std::unique_ptr<ShaderResource>& GetShader(ShaderId id) const;
	const int& ShaderProgram() const;
	const std::unique_ptr<Mesh>& GetMesh(MeshId id) const;
	const std::unique_ptr<Texture>& GetTexture(TextureId id) const;

private:
	void LoadShaders();
	void LoadMeshes();
	void LoadTextures();
};

