#pragma once
#include <memory>
#include <string>
#include "Transform.h"
#include "Camera/Camera.h"
#include "../Resources/Mesh/Mesh.h"
#include "../Resources/Mesh/MeshId.h"
#include "../Resources/Shader/ShaderProgramId.h"
#include "../Resources/Texture/TextureId.h"
#include "../Game/CameraType.h"

class GameObject
{
public:
	enum class PolygonMode;
	struct BuildParams;

protected:
	std::string name;
	Transform transform;
	MeshId meshId;
	ShaderProgramId shaderId;
	TextureId textureId;
	PolygonMode polygonMode;
	CameraType cameraType;

public:
	explicit GameObject(const BuildParams &params);

	virtual void Update();

	Transform& GetTransform();
	MeshId GetMeshId() const;
	ShaderProgramId GetShaderId() const;
	TextureId GetTextureId() const;

	void SetPolygonMode(const PolygonMode &mode);
	gl::GLenum GetPolygonMode() const;

	CameraType Camera() const;

	enum class PolygonMode
	{
		FILL,
		LINE
	};	

	struct BuildParams
	{
		std::string name;
		Transform* parentTransform;
		MeshId meshId;
		ShaderProgramId shaderId;
		TextureId textureId;
		CameraType camera;

		BuildParams();
	};
};
