#include "Fail.h"
#include "ResourceMgr.h"
#include "SoundMgr.h"

Fail::Fail()
{
}

Fail::~Fail()
{
}

void Fail::Initialize()
{
	JoTexture* pFailTex = ResourceMgr::Find<JoTexture>(L"Fail_Text");
	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Fail", pFailTex, Vec2::Zero, Vec2(1368.f, 152.f), Vec2::Zero, 10, 1, 0.15f, true);
	m_pAnimator->GetEvents(L"Fail")->EndEvent = bind(&GameObject::SetDeath, this);
	m_pAnimator->PlayAnimation(L"Fail", false);

	// Play Sound;
}

void Fail::Update()
{
	m_pAnimator->Update();
}

void Fail::Render()
{
	m_pAnimator->Render();
}
