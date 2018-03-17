#pragma once
#include <memory>
#include <string>
#include "Transform.h"
#include "../Resources/Mesh/Mesh.h"
#include "../Resources/Mesh/MeshId.h"
#include "../Resources/Shader/ShaderProgramId.h"
#include "../Resources/Texture/TextureId.h"

class GameObject
{
	std::string name;
	Transform transform;
	MeshId meshId;
	ShaderProgramId shaderId;
	TextureId textureId;

public:
	GameObject(std::string name, Transform* parentTransform, MeshId meshId, ShaderProgramId shaderId, TextureId textureId);

	Transform* GetTransform();
	MeshId GetMeshId() const;
	ShaderProgramId GetShaderId() const;
	TextureId GetTextureId() const;

	
};
