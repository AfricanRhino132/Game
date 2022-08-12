#pragma once
#include "Resource.h"

#include <memory>
#include <map>

namespace neu
{
	class ResourceManager
	{
	public:
		ResourceManager() = default;
		~ResourceManager() = default;

		void Initialize();
		void Shutdown();
		
		template <typename T>
		std::shared_ptr<T> Get(const std::string& key, void* data = nullptr);

	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resources;

	};

	template<typename T>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& key, void* data)
	{
		if (m_resources.find(key) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T>(m_resources[key]);
		}
		else
		{
			std::shared_ptr<T> resource = std::make_shared<T>();

			resource->Create(key, data);

			m_resources[key] = resource;

			return resource;
		}
	}
}