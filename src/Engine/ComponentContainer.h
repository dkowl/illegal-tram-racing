#pragma once
#include <map>
#include <vector>
#include <memory>
#include "Component.h"

class ComponentContainer
{
	
	std::map<ComponentType, std::vector<std::unique_ptr<Component>>> components;

public:
	template <typename T>
	T* AddComponent(typename T::BuildParams p)
	{
		return AddComponent(std::make_unique<T>(p));
	}

	template <typename T>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> result;
		for(auto&& i: components[T::Type()])
		{
			result.push_back(i.get());
		}
		return result;
	}

private:
	template <typename T>
	T* AddComponent(std::unique_ptr<T> &&component)
	{
		T* result = component.get();
		components[T::Type()].emplace_back(std::move(component));
		return result;
	}



};
