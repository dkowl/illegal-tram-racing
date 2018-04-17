#pragma once
#include "ComponentType.h"

class GameObject;

class Component
{
protected:
	GameObject* gameObject;

public:
	explicit Component(GameObject* gameObject = nullptr);
	virtual ~Component() = default;

	virtual void Update();

	GameObject* GetGameObject() const;

	struct BuildParams
	{
		GameObject* gameObject;

		BuildParams();
	};
};
