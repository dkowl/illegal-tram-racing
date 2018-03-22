#include "GameObject.h"

GameObject::GameObject(const BuildParams &params):
	name(params.name),
	meshId(params.meshId),
	shaderId(params.shaderId),
	textureId(params.textureId),
	polygonMode(PolygonMode::FILL),
	cameraType(params.camera)
{
	if(params.parentTransform != nullptr)
	{
		transform.SetParent(params.parentTransform);
	}
}

void GameObject::Update()
{
	std::cout << "Updating " << name << std::endl;
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

CameraType GameObject::Camera() const
{
	return cameraType;
}

GameObject::BuildParams::BuildParams():
	name("New object"),
	parentTransform(nullptr),
	meshId(MeshId::CUBE),
	shaderId(ShaderProgramId::MAIN),
	textureId(TextureId::CRATE),
	camera(CameraType::MAIN)
{
}

Transform& GameObject::GetTransform()
{
	return transform;
}
