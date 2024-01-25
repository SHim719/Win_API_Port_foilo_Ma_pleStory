#include "VellumTrigger.h"
#include "KeyMgr.h"
#include "Vellum.h"
#include "joObject.h"

VellumTrigger::VellumTrigger()
	: m_pVellum(nullptr)
{
}

VellumTrigger::~VellumTrigger()
{
}

void VellumTrigger::Initialize()
{
	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(500.f, 700.f));

}

void VellumTrigger::Update()
{
	Vec2 vMousePos = KeyMgr::GetWorldMousePos();

	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (vMousePos.x > GetPos().x - m_pCollider->GetSize().x * 0.5f
			&& vMousePos.y > GetPos().y - m_pCollider->GetSize().y * 0.5f
			&& vMousePos.x < GetPos().x + m_pCollider->GetSize().x * 0.5f
			&& vMousePos.y < GetPos().y + m_pCollider->GetSize().y * 0.5f)
		{
			m_pVellum->SetActive(true);
			m_pVellum->SetState_Attack1();
			//m_pVellum->SetState_Move();
			Destroy(this);
		}
	}
		
}

void VellumTrigger::Render()
{
	m_pCollider->Render();
}
