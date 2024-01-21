#include "Girl.h"
#include "ResourceMgr.h"

Girl::Girl()
	: m_pTexture(nullptr)
{
}

Girl::~Girl()
{
}

void Girl::Initialize()
{
	m_pTexture = ResourceMgr::Find<JoTexture>(L"ÀÇ¹®ÀÇ ¼Ò³à");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Idle", m_pTexture, Vec2::Zero, Vec2(99.f, 114.f), Vec2::Zero, 12, 0.3f);

	m_pAnimator->PlayAnimation(L"Idle", true);

	SetPos({ 1241.f, 813.f });
}

void Girl::Update()
{
	m_pAnimator->Update();
}

void Girl::LateUpdate()
{
}

void Girl::Render()
{
	m_pAnimator->Render();
}

void Girl::Release()
{
}
