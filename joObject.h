#pragma once

#include "Layer.h"
#include "GameObject.h"
#include "SceneMgr.h"
#include "Scene.h"

template<typename T>
static T* Instantiate(const eLayerType& type)
{
	T* obj = new T();
	obj->Initialize();
	Scene* activeScene = SceneMgr::GetActiveScene();
	activeScene->AddObj(obj, type);

	return obj;
}
static void Destroy(GameObject* obj)
{
	obj->SetDeath();
}
