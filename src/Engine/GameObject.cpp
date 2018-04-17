#include "GameObject.h"

GameObject::GameObject(const BuildParams &params):
	name(params.name),
	cameraType(params.camera)
{
	if(params.parentTransform != nullptr)
	{
		transform.SetParent(params.parentTransform);
	}
}

void GameObject::Update()
{
}

CameraType GameObject::Camera() const
{
	return cameraType;
}

GameObject::BuildParams::BuildParams():
	name("New object"),
	parentTransform(nullptr),
	camera(CameraType::MAIN)
{
}

Transform& GameObject::GetTransform()
{
	return transform;
}
