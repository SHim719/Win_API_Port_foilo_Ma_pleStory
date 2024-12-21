#include "StunEffect.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "joObject.h"

StunEffect::StunEffect()
	: m_pOwner(nullptr)
{
}

StunEffect::~StunEffect()
{

}

void StunEffect::Initialize()
{
	JoTexture* pStunTexture = ResourceMgr::Find<JoTexture>(L"StunEffect");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Stun", pStunTexture, Vec2::Zero, Vec2(66.f, 18.f), Vec2::Zero, 3, 0.2f);
	m_pAnimator->PlayAnimation(L"Stun");
}

void StunEffect::Update()
{
	if (static_cast<Player*>(m_pOwner)->isStunning() == false)
		Destroy(this);

	Vec2 vOwnerPos = m_pOwner->GetPos();
	vOwnerPos.y -= 30.f;
	SetPos(vOwnerPos);

	m_pAnimator->Update();
}

void StunEffect::Render()
{
	m_pAnimator->Render();
}
