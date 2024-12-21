#include "GoodEffect.h"
#include "ResourceMgr.h"
#include "TotemBar.h"
#include "joObject.h"

GoodEffect::GoodEffect()
{
}

GoodEffect::~GoodEffect()
{
}

void GoodEffect::Initialize()
{
	JoTexture* pEffectTex = ResourceMgr::Find<JoTexture>(L"Good");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Active", pEffectTex, Vec2::Zero, Vec2(140.f, 140.f), Vec2::Zero, 11, 0.1f, true);

	m_pAnimator->GetEvents(L"Active")->EndEvent = bind(&GoodEffect::ResetBar, this);

	m_pAnimator->PlayAnimation(L"Active", false);
}

void GoodEffect::Update()
{
	m_pAnimator->Update();
}

void GoodEffect::Render()
{
	m_pAnimator->Render();
}

void GoodEffect::ResetBar()
{
	m_pTotemBar->Set_Start();
	Destroy(this);
}
