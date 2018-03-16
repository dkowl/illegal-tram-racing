#pragma once
#include <memory>
#include <string>
#include "Transform.h"
#include "../Resources/Mesh/Mesh.h"
#include "../Resources/Mesh/MeshId.h"

class GameObject
{
	std::string name;
	Transform transform;
	MeshId meshId;

public:
	GameObject(std::string name, Transform* parentTransform, MeshId meshId);

	Transform* GetTransform();
	
};
