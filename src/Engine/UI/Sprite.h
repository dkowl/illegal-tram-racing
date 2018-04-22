#pragma once
#include "../GameObject.h"
#include "../Components/MeshComponent.h"

class Sprite : public MeshComponent
{
public:
	struct BuildParams;

private:
	float zDepth;

public:
	explicit Sprite(const BuildParams &p);

	static ComponentType Type();

	struct BuildParams : Component::BuildParams
	{
		TextureId textureId;
		float zDepth;

		BuildParams();
	};

	static MeshComponent::BuildParams MeshBuildParams(const BuildParams& p);
};
