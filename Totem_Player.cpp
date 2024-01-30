#include "Totem_Player.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "TotemBar.h"
#include "TS_GameMgr.h"


Totem_Player::Totem_Player()
{
}

Totem_Player::~Totem_Player()
{
}

void Totem_Player::Initialize()
{
	JoTexture* pPlayerTex = ResourceMgr::Find<JoTexture>(L"Player_Totem");
	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Alert", pPlayerTex, Vec2::Zero, Vec2(100.f, 120.f), Vec2::Zero, 3, 0.5f);
	m_pAnimator->CreateAnimation(L"Swing", pPlayerTex, Vec2(300.f, 0.f), Vec2(100.f, 120.f), Vec2::Zero, 8, 0.05f);
	
	m_pAnimator->GetEvents(L"Swing")->EndEvent = bind(&Totem_Player::Play_AlertAnim, this);

	m_pAnimator->PlayAnimation(L"Alert");
}

void Totem_Player::Update()
{
	if (m_pTotemBar->IsWait() == false)
	{
		if (KeyMgr::GetKeyDown(eKeyCode::Space))
		{
			m_pAnimator->PlayAnimation(L"Swing", false);
			int AttackVal = m_pTotemBar->Check_Bar();
			m_pMgr->Slash_Totem(AttackVal);
			//매니져 -> 고정위치 Kill UI 
			// 맨밑 토템위치에 애니메이션 출력! 사운드 재생
		}
	}
	m_pAnimator->Update();
}

void Totem_Player::Render()
{
	m_pAnimator->Render();
}

void Totem_Player::Play_AlertAnim()
{
	m_pAnimator->PlayAnimation(L"Alert");
}
