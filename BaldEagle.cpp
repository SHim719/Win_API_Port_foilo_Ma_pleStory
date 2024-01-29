#include "BaldEagle.h"
#include "ResourceMgr.h"
#include "EG_GameMgr.h"


void BaldEagle::Initialize()
{
	m_pEagleTex = ResourceMgr::Find<JoTexture>(L"Bald_Eagle");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Fly_L", m_pEagleTex, Vec2(2388.f, 0.f), Vec2(167.f, 142.f), Vec2::Zero, 7, 0.2f);
	m_pAnimator->CreateAnimation(L"Fly_R", m_pEagleTex, Vec2(3557.f, 0.f), Vec2(167.f, 142.f), Vec2::Zero, 7, 0.2f);
	m_pAnimator->CreateAnimation(L"Die_L", m_pEagleTex, Vec2(0.f, 0.f), Vec2(199.f, 144.f), Vec2::Zero, 6, 0.2f);
	m_pAnimator->CreateAnimation(L"Die_R", m_pEagleTex, Vec2(199.f * 6, 0.f), Vec2(199.f, 144.f), Vec2::Zero, 6, 0.2f);

	m_pAnimator->GetEvents(L"Die_L")->frameEvents[5] = bind(&GameObject::SetDeath, this);
	m_pAnimator->GetEvents(L"Die_R")->frameEvents[5] = bind(&GameObject::SetDeath, this);

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize({ 160.f, 140.f });

	m_pRigidbody = new Rigidbody;
	m_pRigidbody->SetOwner(this);
	m_pRigidbody->SetUseGravity(false);

	//Set_RandomPos();
	SetPos({ 512.f, 768.f * 0.5f });
	Reset_Dir();

}

void BaldEagle::Hit(const HitInfo& _hitInfo)
{
	m_bDie = true;
	m_pCollider->SetCollisionInactive();
	m_pRigidbody->SetVelocity(Vec2::Zero);
	if (m_vDir.x > 0.f)
		m_pAnimator->PlayAnimation(L"Die_R", false);
	else
		m_pAnimator->PlayAnimation(L"Die_L", false);

	s_pGameMgr->Minus_BaldCnt();
}
