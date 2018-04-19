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
}

void PbrLight::SetGlUniforms()
{
	auto& pbrShader = Game::Resources().Get(ShaderProgramId::PBR);
	pbrShader->SetVec3("lightColor", color);
	pbrShader->SetVec3("lightPosition", gameObject->GetTransform().Position());
}

PbrLight::BuildParams::BuildParams():
	color(1, 1, 1),
	intensity(1),
	attenuationFactor(1)
{
}
