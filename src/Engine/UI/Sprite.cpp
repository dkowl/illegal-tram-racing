#include "Sprite.h"

Sprite::Sprite(const BuildParams& p):
	MeshComponent(MeshBuildParams(p)),
	zDepth(p.zDepth)
{
	gameObject->GetTransform().Move(glm::vec3(0, 0, zDepth));
}

ComponentType Sprite::Type()
{
	return ComponentType::SPRITE;
}

Sprite::BuildParams::BuildParams():
	textureId(TextureId::CRATE),
	zDepth(0)	
{
}

MeshComponent::BuildParams Sprite::MeshBuildParams(const BuildParams& p)
{
	MeshComponent::BuildParams result;
	result.gameObject = p.gameObject;
	result.shaderId = ShaderProgramId::MAIN;
	result.cameraType = CameraType::UI;
	result.meshId = MeshId::PLANE;
	result.textureIds = { p.textureId };

	return result;
}
