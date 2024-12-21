#include "PerfectEffect.h"
#include "ResourceMgr.h"
#include "TotemBar.h"
#include "SoundMgr.h"
#include "joObject.h"

PerfectEffect::PerfectEffect()
{
}

PerfectEffect::~PerfectEffect()
{
}

void PerfectEffect::Initialize()
{
	JoTexture* pEffectTex = ResourceMgr::Find<JoTexture>(L"Perfect");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Active", pEffectTex, Vec2::Zero, Vec2(328.f, 285.f), Vec2(0.f, -20.f), 11, 0.1f, true);

	m_pAnimator->GetEvents(L"Active")->EndEvent = bind(&PerfectEffect::ResetBar, this);

	m_pAnimator->PlayAnimation(L"Active", false);

	SoundMgr::Play(L"Perfect_SFX");
}

void PerfectEffect::Update()
{
	m_pAnimator->Update();
}

void PerfectEffect::Render()
{
	m_pAnimator->Render();
}

void PerfectEffect::ResetBar()
{
	m_pTotemBar->Set_Start();
	Destroy(this);
}
