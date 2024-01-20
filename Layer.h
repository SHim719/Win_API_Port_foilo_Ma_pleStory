#pragma once

#include "CommonInclude.h"

class GameObject;

class Layer
{
public:
	Layer();
	~Layer();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	void Destroy();

	void AddObj(GameObject* const pObj) { m_ObjList.push_back(pObj); }

	const list<GameObject*>& GetGameObjects() const { return m_ObjList; }
private:
	list<GameObject*> m_ObjList;
};

