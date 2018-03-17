#pragma once
#include <memory>

#include "../glbinding.h"

#include "Mesh/Mesh.h"
#include "Mesh/MeshId.h"
#include "Texture/Texture.h"
#include "Texture/TextureId.h"
#include "Shader/ShaderSource.h"
#include "Shader/ShaderSourceId.h"
#include "Shader/ShaderProgram.h"
#include "Shader/ShaderProgramId.h"

class Resources
{
	std::unique_ptr<ShaderSource> shaderSources[int(ShaderSourceId::COUNT)];
	std::unique_ptr<ShaderProgram> shaderPrograms[int(ShaderProgramId::COUNT)];

	std::unique_ptr<Mesh> meshes[int(MeshId::COUNT)];
	std::unique_ptr<Texture> textures[int(TextureId::COUNT)];
public:
	Resources();
	void Initialize();

	const std::unique_ptr<ShaderSource>& GetShaderSource(ShaderSourceId id) const;
	const std::unique_ptr<ShaderProgram>& GetShaderProgram(ShaderProgramId id) const;
	const std::unique_ptr<Mesh>& GetMesh(MeshId id) const;
	const std::unique_ptr<Texture>& GetTexture(TextureId id) const;

private:
	void CompileShaders();
	void LinkShaderPrograms();
	void LoadMeshes();
	void LoadTextures();
};

