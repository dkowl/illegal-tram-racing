#pragma once
#include "PbrLight.h"

class DirectionalLight : public PbrLight
{
	static const float DISTANCE;
	
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);

	static PbrLight::BuildParams MakeBuildParams(glm::vec3 direction, glm::vec3 color, float intensity);
};
