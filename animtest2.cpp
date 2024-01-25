#include "animtest2.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"



void animtest2::Initialize()
{
	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	JoTexture* pTest = ResourceMgr::Load<JoTexture>(L"Breath", L"Resources/Enemy/Vellum/Breath.png");

	m_pAnimator->CreateAnimation(L"Breath", pTest, Vec2::Zero, Vec2(341.f, 810.f), Vec2::Zero, 6, 0.1f);

	m_pAnimator->PlayAnimation(L"Breath");
}

void animtest2::Update()
{
	m_pAnimator->Update();
}

void animtest2::Render()
{
	m_pAnimator->Render();
}
