#pragma once
#include <memory>
#include <vector>
#include <string>
#include <map>

template <typename T, typename TEnum>
class Resource
{
	std::unique_ptr<T> instances[unsigned int(TEnum::COUNT)];
	std::vector<std::unique_ptr<T>> dynamicInstances;
	std::map<std::string, int> instanceIdMap;

public:
	const std::unique_ptr<T>& Get(TEnum id) const
	{
		return instances[int(id)];
	}

	int AddDynamic(std::unique_ptr<T> &&resource, const std::string& name)
	{
		dynamicInstances.emplace_back(std::move(resource));
		const int id = dynamicInstances.size() - 1;
		instanceIdMap[name] = id;
		return id;
	}

	T* GetDynamic(const int& id)
	{
		if(id < 0 || id >= dynamicInstances.size())
		{
			std::cout << "Invalid resource instance id\n" << std::endl;
			return nullptr;
		}
		return dynamicInstances[id].get();
	}

	T* GetDynamic(const std::string& name)
	{
		if(instanceIdMap.find(name) == instanceIdMap.end())
		{
			std::cout << "Resource " << name << " not found\n";
			return nullptr;
		}
		return GetDynamic(instanceIdMap[name]);
	}

protected:
	void Set(TEnum id, std::unique_ptr<T> &&resource)
	{
		instances[int(id)] = std::move(resource);
	}

};
