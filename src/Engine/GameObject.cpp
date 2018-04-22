#include "GameObject.h"

GameObject::GameObject(const BuildParams &params):
	name(params.name)
{
	if(params.parentTransform != nullptr)
	{
		transform.SetParent(params.parentTransform);
	}
}

void GameObject::Update()
{
}

GameObject::BuildParams::BuildParams():
	name("New object"),
	parentTransform(nullptr)
{
}

Transform& GameObject::GetTransform()
{
	return transform;
}
