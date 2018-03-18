#include "GameObject.h"

GameObject::GameObject(std::string name, Transform* parentTransform, MeshId meshId, ShaderProgramId shaderId, TextureId textureId):
	name(name),
	meshId(meshId),
	shaderId(shaderId),
	textureId(textureId)
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

ShaderProgramId GameObject::GetShaderId() const
{
	return shaderId;
}

TextureId GameObject::GetTextureId() const
{
	return textureId;
}

Transform& GameObject::GetTransform()
{
	return transform;
}
