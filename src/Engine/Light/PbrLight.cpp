#include "PbrLight.h"
#include "../../Game/Game.h"
#include "../GameObject.h"

ComponentType PbrLight::Type()
{
	return ComponentType::LIGHT;
}

PbrLight::PbrLight(BuildParams p):
	Component(p.gameObject),
	color(p.color),
	intensity(p.intensity),
	attenuationFactor(p.attenuationFactor)
{
	gameObject->GetTransform().SetLocalPosition(p.position);
}

void PbrLight::SetGlUniforms() const
{
	auto& pbrShader = Game::Resources().Get(ShaderProgramId::PBR);
	std::cout << "LightColor is ";
	Utils::DisplayVec3(color * intensity);
	pbrShader->Use();
	pbrShader->SetVec3("LightColor", color * intensity);
	pbrShader->SetVec3("LightPosition", gameObject->GetTransform().Position());
	pbrShader->SetFloat("AttenuationFactor", attenuationFactor);
}

PbrLight::BuildParams::BuildParams():
	color(1, 1, 1),
	intensity(1),
	attenuationFactor(1)
{
}
