#pragma once
#include <memory>

template <typename T, typename TEnum, unsigned int TCount>
class Resource
{
	std::unique_ptr<T> instances[TCount];

public:
	const std::unique_ptr<T>& Get(TEnum id)
	{
		return instances[int(id)];
	}

protected:
	void Set(TEnum id, std::unique_ptr<T> &&resource)
	{
		instances[int(id)] = std::move(resource);
	}

};
