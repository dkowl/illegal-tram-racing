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

MeshId GameObject::GetMeshId() const
{
	return meshId;
}

Transform* GameObject::GetTransform()
{
	return &transform;
}
