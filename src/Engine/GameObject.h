#pragma once
#include <vector>
#include <string>
#include <map>

#include "../glbinding.h"

#include "Transform.h"
#include "../Game/CameraType.h"
#include "../Game/Game.h"
#include "ComponentType.h"

class Component;

class GameObject
{
public:
	enum class PolygonMode;
	struct BuildParams;

private:
	std::map<ComponentType, Component*> components;

protected:
	std::string name;
	Transform transform;

public:
	explicit GameObject(const BuildParams &params);

	template<typename T> void AddComponent(typename T::BuildParams p);
	template<typename T> T* GetComponent();

	virtual void Update();

	Transform& GetTransform();
	CameraType Camera() const;	

	struct BuildParams
	{
		std::string name;
		Transform* parentTransform;

		BuildParams();
	};
};

template<typename T>
void GameObject::AddComponent(typename T::BuildParams p)
{
	p.gameObject = this;
	T* component = Game::Components().AddComponent<T>(p);
	components[T::Type()] = component;
}

template<typename T>
T* GameObject::GetComponent()
{
	if (components.find(T::Type()) == components.end()) return nullptr;
	return static_cast<T*>(components[T::Type()]);
}
