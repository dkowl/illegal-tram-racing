#pragma once
#include <memory>
#include <string>
#include "Transform.h"
#include "Camera.h"
#include "../Resources/Mesh/Mesh.h"
#include "../Resources/Mesh/MeshId.h"
#include "../Resources/Shader/ShaderProgramId.h"
#include "../Resources/Texture/TextureId.h"


class GameObject
{
public:
	enum class PolygonMode;

private:
	std::string name;
	Transform transform;
	MeshId meshId;
	ShaderProgramId shaderId;
	TextureId textureId;
	PolygonMode polygonMode;
	Camera *camera;

public:
	GameObject(std::string name, Transform* parentTransform, MeshId meshId, ShaderProgramId shaderId, TextureId textureId, Camera* camera);

	Transform& GetTransform();
	MeshId GetMeshId() const;
	ShaderProgramId GetShaderId() const;
	TextureId GetTextureId() const;

	void SetPolygonMode(const PolygonMode &mode);
	gl::GLenum GetPolygonMode() const;

	Camera* GetCamera() const;

	enum class PolygonMode
	{
		FILL,
		LINE
	};	
};
