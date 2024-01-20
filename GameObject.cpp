#include "GameObject.h"


GameObject::GameObject()
	: m_tTransform{}
	, m_eLifeCycle(eLifeCycle::Active)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidbody(nullptr)
{	  
}

GameObject::~GameObject()
{
	GameObject::Release();
}

void GameObject::Initialize()
{
}

void GameObject::Update()
{
}

void GameObject::LateUpdate()
{
}

void GameObject::Render()
{
}

void GameObject::Release()
{
	Safe_Delete<Collider*>(m_pCollider);
	Safe_Delete<Animator*>(m_pAnimator);
	Safe_Delete<Rigidbody*>(m_pRigidbody);
}
	