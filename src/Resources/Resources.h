#pragma once
#include <memory>

#include "../glbinding.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh/Mesh.h"
#include "Mesh/MeshId.h"
#include "Texture/Texture.h"
#include "Texture/TextureId.h"
#include "Shader/ShaderSource.h"
#include "Shader/ShaderSourceId.h"
#include "Shader/ShaderProgram.h"
#include "Shader/ShaderProgramId.h"
#include "MeshLayout/MeshLayout.h"
#include "MeshLayout/MeshLayoutId.h"
#include "../Game/Track.h"
#include "Resource.h"

#define RESOURCE_BASE(T) Resource< T , T ## Id>

#define USING_RESOURCE(T) \
	using RESOURCE_BASE(T)::Get;\
	using RESOURCE_BASE(T)::Set;

class Resources : 
	public RESOURCE_BASE(ShaderSource),
	public RESOURCE_BASE(MeshLayout),
	public RESOURCE_BASE(ShaderProgram)
{
public:
	USING_RESOURCE(ShaderSource)
	USING_RESOURCE(MeshLayout)
	USING_RESOURCE(ShaderProgram)

private:
	std::unique_ptr<Mesh> meshes[int(MeshId::COUNT)];
	std::unique_ptr<Texture> textures[int(TextureId::COUNT)];

	std::unique_ptr<Track> track;
public:
	Resources();
	void Initialize();

	const std::unique_ptr<Mesh>& GetMesh(MeshId id) const;
	const std::unique_ptr<Texture>& GetTexture(TextureId id) const;

	const std::unique_ptr<Track>& GetTrack() const;

private:
	void CompileShaders();
	void LinkShaderPrograms();

	void LoadTracks();

	void LoadMeshLayouts();
	void LoadMeshes();
	void LoadPrimitiveMeshes();
	void LoadTram();

	void LoadTextures();
};

