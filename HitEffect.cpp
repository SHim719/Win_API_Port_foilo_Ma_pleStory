#include "HitEffect.h"
#include "joObject.h"

HitEffect::HitEffect()
	: m_pEffectTex(nullptr)
{
}

HitEffect::~HitEffect()
{
}

void HitEffect::Initialize()
{
	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	
	m_pAnimator->CreateAnimation(L"Hit_Anim", m_pEffectTex, Vec2::Zero, m_vSize,
		m_vOffset, m_iSpriteLength, m_fDuration);

	m_pAnimator->PlayAnimation(L"Hit_Anim", false);
}

void HitEffect::Update()
{
	if (m_pAnimator->IsEndAnim())
		Destroy(this);

	m_pAnimator->Update();
}

void HitEffect::LateUpdate()
{
}

void HitEffect::Render()
{
	m_pAnimator->Render();
}
