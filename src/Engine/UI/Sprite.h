#pragma once
#include "../GameObject.h"

class Sprite : public GameObject
{
public:
	struct BuildParams;

private:
	float zDepth;

public:
	explicit Sprite(const BuildParams &params);

	struct BuildParams
	{
		std::string name;
		Transform* parentTransform;
		TextureId textureId;
		float zDepth;

		BuildParams();
		explicit operator GameObject::BuildParams() const;
	};
};
