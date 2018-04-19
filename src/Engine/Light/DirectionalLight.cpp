#include "DirectionalLight.h"
#include "../GameObject.h"

const float DirectionalLight::DISTANCE = 1000000;

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity):
	PbrLight(MakeBuildParams(direction, color, intensity))
{
}

PbrLight::BuildParams DirectionalLight::MakeBuildParams(glm::vec3 direction, glm::vec3 color, float intensity)
{
	PbrLight::BuildParams p;
	p.position = glm::normalize(direction) * -1.f * DISTANCE;
	p.attenuationFactor = 0;
	p.color = color;
	p.intensity = intensity;

	return p;
}
