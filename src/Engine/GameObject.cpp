#include "GameObject.h"

GameObject::GameObject(const BuildParams &params):
	name(params.name),
	meshId(params.meshId),
	shaderId(params.shaderId),
	textureIds(params.textureIds),
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
}

MeshId GameObject::GetMeshId() const
{
	return meshId;
}

ShaderProgramId GameObject::GetShaderId() const
{
	return shaderId;
}

TextureId GameObject::GetTextureId(unsigned id) const
{
	return textureIds[id];
}

std::vector<TextureId> GameObject::GetTextureIds() const
{
	return textureIds;
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
	textureIds({ TextureId::CRATE }),
	camera(CameraType::MAIN)
{
}

Transform& GameObject::GetTransform()
{
	return transform;
}
