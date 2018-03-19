#include "GameObject.h"

GameObject::GameObject(std::string name, Transform* parentTransform, MeshId meshId, ShaderProgramId shaderId, TextureId textureId):
	name(name),
	meshId(meshId),
	shaderId(shaderId),
	textureId(textureId),
	polygonMode(PolygonMode::FILL)
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

void GameObject::SetPolygonMode(const PolygonMode &mode)
{
	polygonMode = mode;
}

gl::GLenum GameObject::GetPolygonMode() const
{
	switch (polygonMode)
	{
	case PolygonMode::FILL:
		return gl::GLenum::GL_FILL;
	case PolygonMode::LINE:
		return gl::GLenum::GL_LINE;
	}
}

Transform& GameObject::GetTransform()
{
	return transform;
}
