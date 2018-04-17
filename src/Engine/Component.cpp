#include "Component.h"

Component::Component(GameObject* gameObject):
	gameObject(gameObject)
{
}

void Component::Update()
{
}

GameObject* Component::GetGameObject() const
{
	return gameObject;
}

Component::BuildParams::BuildParams():
	gameObject(nullptr)
{
}
