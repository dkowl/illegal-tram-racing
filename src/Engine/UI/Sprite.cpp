#include "Sprite.h"

Sprite::Sprite(const BuildParams &params):
	GameObject(GameObject::BuildParams(params)),
	zDepth(params.zDepth)
{
	transform.Move(glm::vec3(0, 0, zDepth));
}

Sprite::BuildParams::BuildParams()
{
	name = "New sprite";
	parentTransform = nullptr;
	textureId = TextureId::CRATE;
	zDepth = 0;
}

Sprite::BuildParams::operator GameObject::BuildParams() const
{
	GameObject::BuildParams result;
	result.name = name;
	result.parentTransform = parentTransform;
	result.camera = CameraType::UI;
	return result;
}
