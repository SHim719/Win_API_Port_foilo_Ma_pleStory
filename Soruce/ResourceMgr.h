#pragma once

#include "JoResource.h"
#include "JoTexture.h"
#include "JoBmp.h"
#include "Audio.h"

class ResourceMgr
{
public:
	template <typename T>
	static T* Find(const wstring& key)
	{
		auto it = m_resources.find(key);

		if (it == m_resources.end())
			return nullptr;

		return dynamic_cast<T*>(it->second);
	}

	template <typename T>
	static T* Load(const wstring& key, const wstring& path)
	{
		T* resource = ResourceMgr::Find<T>(key);
		if (resource != nullptr)
			return resource;

		resource = new T();
		if (FAILED(resource->Load(path)))
			assert(false);

		resource->SetName(key);
		resource->SetPath(path);
		m_resources.insert({ key, resource });

		return resource;
	}

	static void Initialize();
	static void Release();

private:
	static map<wstring, JoResource*> m_resources;
};

