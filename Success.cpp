#include "Success.h"
#include "ResourceMgr.h"
#include "SoundMgr.h"


Success::Success()
{
}

Success::~Success()
{
}

void Success::Initialize()
{
	JoTexture* pClearTex = ResourceMgr::Find<JoTexture>(L"Clear_Text");
	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Clear", pClearTex, Vec2::Zero, Vec2(591.f, 163.f), Vec2::Zero, 10, 1, 0.15f, true);

	m_pAnimator->GetEvents(L"Clear")->EndEvent = bind(&GameObject::SetDeath, this);
	m_pAnimator->PlayAnimation(L"Clear", false);

	// Play Sound;
}

void Success::Update()
{
	m_pAnimator->Update();
}

void Success::Render()
{
	m_pAnimator->Render();
}
