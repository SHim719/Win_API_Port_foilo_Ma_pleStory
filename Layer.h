#pragma once

#include "CommonInclude.h"

class GameObject;

class Layer
{
public:
	Layer();
	~Layer();

	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	void Destroy();

	void AddObj(GameObject* const pObj) { m_ObjList.push_back(pObj); }

	const list<GameObject*>& GetGameObjects() const { return m_ObjList; }
private:
	list<GameObject*> m_ObjList;
};

