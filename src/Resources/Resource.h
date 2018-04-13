#pragma once
#include <memory>

template <typename T, typename TEnum>
class Resource
{
	std::unique_ptr<T> instances[unsigned int(TEnum::COUNT)];

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
