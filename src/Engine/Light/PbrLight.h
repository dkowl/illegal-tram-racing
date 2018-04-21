#pragma once

#include <glm/glm.hpp>
#include "../Component.h"

class PbrLight : public Component
{
public:
	struct BuildParams;

protected:
	glm::vec3 color;
	float intensity;
	float attenuationFactor;

public:
	static ComponentType Type();

	explicit PbrLight(BuildParams p);

	void SetGlUniforms() const;

	struct BuildParams : Component::BuildParams
	{
		glm::vec3 position;
		glm::vec3 color;
		float intensity;
		float attenuationFactor;

		BuildParams();
	};


	
};
