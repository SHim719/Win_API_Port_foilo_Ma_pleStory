#pragma once

#include "Scene.h"

class SceneMgr
{
public:
	template<typename T>
	static void CreateScene(const wstring& name)
	{
		T* scene = new T();
		m_ActiveScene = scene;
		scene->SetName(name);
		scene->Initialize();

		m_mScenes.insert({ name, scene });
	}
	static void LoadScene(const wstring& name);
	static Scene* GetActiveScene() { return m_ActiveScene; }

	static void Initialize();
	static void Update();
	static void LateUpdate();
	static void Render();
	static void Destroy();

private:
	static map<const wstring, Scene*> m_mScenes;
	static Scene* m_ActiveScene;

};

