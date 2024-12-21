#include "GreatEffect.h"
#include "ResourceMgr.h"
#include "TotemBar.h"
#include "joObject.h"

GreatEffect::GreatEffect()
{
}

GreatEffect::~GreatEffect()
{
}

void GreatEffect::Initialize()
{
	JoTexture* pEffectTex = ResourceMgr::Find<JoTexture>(L"Great");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Active", pEffectTex, Vec2::Zero, Vec2(207.5, 205.f), Vec2::Zero, 11, 0.1f, true);

	m_pAnimator->GetEvents(L"Active")->EndEvent = bind(&GreatEffect::ResetBar, this);

	m_pAnimator->PlayAnimation(L"Active", false);
}

void GreatEffect::Update()
{
	m_pAnimator->Update();
}

void GreatEffect::Render()
{
	m_pAnimator->Render();
}

void GreatEffect::ResetBar()
{
	m_pTotemBar->Set_Start();
	Destroy(this);
}
