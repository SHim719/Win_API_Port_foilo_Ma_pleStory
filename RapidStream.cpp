#include "RapidStream.h"
#include "Player.h"

RapidStream::RapidStream()
	: m_fAddVelocityX(0.f)
{
}

RapidStream::~RapidStream()
{
}

void RapidStream::Initialize()
{
	SetPos({ 2837.f, 1100.f });

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(5675.f, 200.f));

	m_fAddVelocityX = 200.f;
}


void RapidStream::OnCollisionEnter(Collider* _pOther)
{
	Player* pPlayer = static_cast<Player*>(_pOther->GetOwner());
	pPlayer->SetState_Swim(true);
}

void RapidStream::OnCollisionStay(Collider* _pOther)
{
}

void RapidStream::OnCollisionExit(Collider* _pOther)
{
	Player* pPlayer = static_cast<Player*>(_pOther->GetOwner());
	if (pPlayer->IsInputJumping())
	{
		pPlayer->GetRigidbody()->AddVelocity(Vec2(0.f, -500.f));
	}
	pPlayer->SetState_Air();
}
