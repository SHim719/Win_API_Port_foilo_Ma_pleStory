#include "Counting.h"
#include "ResourceMgr.h"

Counting::Counting()
{
}

Counting::~Counting()
{
}

void Counting::Initialize()
{
	JoTexture* pCountTex = ResourceMgr::Find<JoTexture>(L"Count_Num");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"Counting", pCountTex, Vec2::Zero, Vec2(102.f, 182.f), Vec2::Zero, 9, 0.1f, true);

	Animation* pAnim = m_pAnimator->FindAnimation(L"Counting");
	pAnim->Set_AnimDuration(2, 0.8f);
	pAnim->Set_AnimDuration(5, 0.8f);
	pAnim->Set_AnimDuration(8, 0.8f);

	m_pAnimator->GetEvents(L"Counting")->EndEvent = bind(&GameObject::SetDeath, this);

	m_pAnimator->PlayAnimation(L"Counting", false);
}

void Counting::Update()
{
	m_pAnimator->Update();
}

void Counting::Render()
{
	m_pAnimator->Render();
}
