#include "MeshComponent.h"
#include "../../Game/Game.h"
#include "../../Engine/GameObject.h"

MeshComponent::MeshComponent(BuildParams p):
	Component(p.gameObject),
	meshId(p.meshId),
	shaderId(p.shaderId),
	textureIds(p.textureIds),
	polygonMode(p.polygonMode),
	cameraType(p.cameraType)
{
}

void MeshComponent::Render() const
{
	const auto& object = gameObject;
	const auto& shaderProgram = Game::Resources().Get(shaderId)->GlId();
	const auto& textures = GetTextureGlIds();
	const auto& mesh = Game::Resources().Get(meshId);

	//shader
	gl::glUseProgram(shaderProgram);

	const unsigned int modelLocation = gl::glGetUniformLocation(shaderProgram, "model");
	gl::glUniformMatrix4fv(modelLocation, 1, gl::GL_FALSE, glm::value_ptr(object->GetTransform().ModelMatrix()));

	const unsigned int viewLocation = gl::glGetUniformLocation(shaderProgram, "view");
	gl::glUniformMatrix4fv(viewLocation, 1, gl::GL_FALSE, glm::value_ptr(Game::I().GetCamera(cameraType)->ViewMatrix()));

	const unsigned int projectionLocation = gl::glGetUniformLocation(shaderProgram, "projection");
	gl::glUniformMatrix4fv(projectionLocation, 1, gl::GL_FALSE, glm::value_ptr(Game::I().GetCamera(cameraType)->ProjectionMatrix()));

	//textures
	for (int i = 0; i < textures.size(); i++)
	{
		gl::glActiveTexture(gl::GLenum::GL_TEXTURE0 + i);
		gl::glBindTexture(gl::GLenum::GL_TEXTURE_2D, textures[i]);
	}

	//mesh
	gl::glBindVertexArray(mesh->Vao());

	gl::glPolygonMode(gl::GLenum::GL_FRONT_AND_BACK, GetPolygonMode());
	gl::glDrawElements(gl::GLenum::GL_TRIANGLES, mesh->ElementCount(), gl::GLenum::GL_UNSIGNED_INT, nullptr);
}

std::vector<unsigned> MeshComponent::GetTextureGlIds() const
{
	std::vector<unsigned> result;
	auto textureIds = GetTextureIds();
	for (auto&& i : textureIds)
	{
		result.push_back(Game::Resources().Get(i)->GlId());
	}
	return result;
}

MeshId MeshComponent::GetMeshId() const
{
	return meshId;
}

ShaderProgramId MeshComponent::GetShaderId() const
{
	return shaderId;
}

TextureId MeshComponent::GetTextureId(unsigned id) const
{
	return textureIds[id];
}

const std::vector<TextureId>& MeshComponent::GetTextureIds() const
{
	return textureIds;
}

gl::GLenum MeshComponent::GetPolygonMode() const
{
	switch (polygonMode)
	{
	case PolygonMode::FILL:
		return gl::GLenum::GL_FILL;
	case PolygonMode::LINE:
		return gl::GLenum::GL_LINE;
	default:
		return gl::GLenum::GL_FILL;
	}
}

CameraType MeshComponent::GetCameraType() const
{
	return cameraType;
}

ComponentType MeshComponent::Type()
{
	return ComponentType::MESH;
}

MeshComponent::BuildParams::BuildParams():
	meshId(MeshId::CUBE),
	shaderId(ShaderProgramId::MAIN),
	textureIds({TextureId::CRATE}),
	polygonMode(PolygonMode::FILL),
	cameraType(CameraType::MAIN)
{
}
