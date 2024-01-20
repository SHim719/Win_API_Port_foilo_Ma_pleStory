#include "Layer.h"
#include "GameObject.h"


Layer::Layer()
	: m_ObjList{}
{
}

Layer::~Layer()
{
}

void Layer::Initialize()
{
	for (GameObject* Obj : m_ObjList)
		Obj->Initialize();
}

void Layer::Update()
{
	/*for (int i = 0; i < m_ObjList.size(); ++i)
	{
		GameObject* Obj = m_ObjList[i];
		if (Obj->IsActive())
			Obj->Update();
	}*/
	for (GameObject* Obj : m_ObjList)
	{
		if (Obj->IsActive())
			Obj->Update();
	}
}


void Layer::LateUpdate()
{
	for (GameObject* Obj : m_ObjList)
	{
		if (Obj->IsActive())
			Obj->LateUpdate();
	}
}

void Layer::Render()
{
	for (GameObject* Obj : m_ObjList)
	{
		if (Obj->IsActive())
			Obj->Render();
	}
}

void Layer::Destroy()
{
	for (auto it = m_ObjList.begin(); it != m_ObjList.end();)
	{
		if ((*it)->IsDeath())
		{
			Safe_Delete<GameObject*>(*it);
			it = m_ObjList.erase(it);
		}
		else
		{
			++it;
		}
	}
}
