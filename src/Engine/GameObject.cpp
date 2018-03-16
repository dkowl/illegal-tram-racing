#include "GameObject.h"

GameObject::GameObject(std::string name, Transform* parentTransform, MeshId meshId):
	name(name),
	meshId(meshId)
{
	if(parentTransform != nullptr)
	{
		transform.SetParent(parentTransform);
	}
}

Transform* GameObject::GetTransform()
{
	return &transform;
}
