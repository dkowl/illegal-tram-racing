#pragma once
#include <vector>
#include <glbinding/gl/enum.h>
#include "../Component.h"
#include "../../Resources/Mesh/MeshId.h"
#include "../../Resources/Shader/ShaderProgramId.h"
#include "../../Resources/Texture/TextureId.h"

class MeshComponent : public Component
{
	enum class PolygonMode;
	struct BuildParams;
	
	MeshId meshId;
	ShaderProgramId shaderId;
	std::vector<TextureId> textureIds;
	PolygonMode polygonMode;

public:
	static ComponentType Type();

	explicit MeshComponent(BuildParams p);

	void Render() const; 
	std::vector<unsigned> GetTextureGlIds() const;

	MeshId GetMeshId() const;
	ShaderProgramId GetShaderId() const;
	TextureId GetTextureId(unsigned id) const;
	const std::vector<TextureId>& GetTextureIds() const;
	gl::GLenum GetPolygonMode() const;

	enum class PolygonMode
	{
		FILL,
		LINE
	};

	struct BuildParams : public Component::BuildParams
	{
		MeshId meshId;
		ShaderProgramId shaderId;
		std::vector<TextureId> textureIds;
		PolygonMode polygonMode;

		BuildParams();
	};
};
