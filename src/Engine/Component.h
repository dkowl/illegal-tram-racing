#pragma once
#include "ComponentType.h"

class GameObject;

class Component
{
protected:
	GameObject* gameObject;

public:
	explicit Component(GameObject* gameObject);
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	void operator=(const Component& other) = delete;
	Component(const Component&& other) = delete;
	void operator=(const Component&& other) = delete;


	virtual void Update();

	GameObject* GetGameObject() const;

	struct BuildParams
	{
		GameObject* gameObject;

		BuildParams();
	};
};
