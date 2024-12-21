#include "KillEffect.h"
#include "ResourceMgr.h"
#include "joObject.h"

void KillEffect::Initialize(const int& _iNum, const Vec2& _vSize)
{
	JoTexture* pTex = nullptr;

	if (_iNum == 2)
		pTex = ResourceMgr::Find<JoTexture>(L"2Kill");
	else
		pTex = ResourceMgr::Find<JoTexture>(L"4Kill");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Active", pTex, Vec2::Zero, _vSize, Vec2(0.f, 0.f), 8, 0.1f, true);

	m_pAnimator->GetEvents(L"Active")->EndEvent = bind(&GameObject::SetDeath, this);

	m_pAnimator->PlayAnimation(L"Active", false);
}

void KillEffect::Update()
{
	m_pAnimator->Update();
}

void KillEffect::Render()
{
	m_pAnimator->Render();
}


