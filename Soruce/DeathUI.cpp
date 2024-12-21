#include "DeathUI.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "Player.h"
#include "RenderMgr.h"

DeathUI::DeathUI()
	: m_pPlayer(nullptr)
	, m_bActive(false)
{
}

DeathUI::~DeathUI()
{
}

void DeathUI::Initialize()
{
	m_pMainTex = ResourceMgr::Load<JoTexture>(L"DeathUI", L"Resources/UI/Death/DeathUI.png");

	m_vPos = { 400.f, 200.f };
}

void DeathUI::Update()
{
	if (!m_bActive)
		return;

	m_vMousePos = KeyMgr::GetMousePos();

	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (UIMgr::IsMouseUsed() == false)
		{
			bool bFocused = Check_Focused();
			UIMgr::SetMouseUsed(bFocused);
			if (UIMgr::IsMouseUsed() == true)
			{
				Check_Button();
			}
		}
	}
}

void DeathUI::LateUpdate()
{
}

void DeathUI::Render()
{
	if (!m_bActive)
		return;
	RenderMgr::RenderImage(m_pMainTex
		, m_vPos.x
		, m_vPos.y
		, m_vPos.x + float(m_pMainTex->GetWidth())
		, m_vPos.y + float(m_pMainTex->GetHeight()));
}

void DeathUI::Release()
{
}

void DeathUI::OnInActive()
{
}

void DeathUI::OnActive()
{
}

void DeathUI::Check_Button()
{
	Vec2 buttonPos = m_vPos;
	buttonPos += Vec2(120.f, 100.f);

	if (m_vMousePos.x >= buttonPos.x
		&& m_vMousePos.y >= buttonPos.y
		&& m_vMousePos.x <= buttonPos.x + 58.f
		&& m_vMousePos.y <= buttonPos.y + 21.f)
	{
		SoundMgr::Play(L"Bt_Click");
		if (m_pPlayer)
		{
			m_pPlayer->Revive();
			m_bActive = false;
		}
			
	}

}
