#include "ShopBoy.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "ShopUI.h"

ShopBoy::ShopBoy()
	: m_pTexture(nullptr)
{
}

ShopBoy::~ShopBoy()
{
}

void ShopBoy::Initialize()
{
	m_pTexture = ResourceMgr::Find<JoTexture>(L"¿ÀÄÚ");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Idle", m_pTexture, Vec2::Zero, Vec2(86.f, 90.f), Vec2::Zero, 12, 0.3f);

	m_pAnimator->PlayAnimation(L"Idle", true);

	SetPos({ 1550.f, 387.f });
}

void ShopBoy::Update()
{
	m_pAnimator->Update();
}

void ShopBoy::LateUpdate()
{
}

void ShopBoy::Render()
{
	m_pAnimator->Render();
}

void ShopBoy::Release()
{
}
