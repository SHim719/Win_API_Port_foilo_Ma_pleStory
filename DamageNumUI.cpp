#include "DamageNumUI.h"
#include "RenderMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "DamageNum.h"

DamageNumUI::DamageNumUI()
{
}

DamageNumUI::~DamageNumUI()
{
}

void DamageNumUI::Initialize()
{
	m_vPos = { 220.f, 260.f };

	m_pMainTex = ResourceMgr::Find<JoTexture>(L"Damaged_Num_UI");
	m_vFontSelOffset = { 40.f, 90.f };
	m_vModeSelOffset = { 35.f, 180.f };

}

void DamageNumUI::Update()
{
	m_vMousePos = KeyMgr::GetMousePos();

	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (UIMgr::IsMouseUsed() == false)
		{
			bool bFocused = Check_Focused();
			UIMgr::SetMouseUsed(bFocused);
			if (UIMgr::IsMouseUsed() == true)
			{
				if (Check_Number())
					return;
				
				Check_Mode();
			}
		}
	}
}

void DamageNumUI::LateUpdate()
{
}

void DamageNumUI::Render()
{
	RenderMgr::RenderImage(m_pMainTex
		, m_vPos.x, m_vPos.y
		, m_vPos.x + m_pMainTex->GetWidth(), m_vPos.y + m_pMainTex->GetHeight());
}

void DamageNumUI::Release()
{
}

void DamageNumUI::OnInActive()
{
	SoundMgr::Play(L"CloseWindow");
}

void DamageNumUI::OnActive()
{
	SoundMgr::Play(L"OpenWindow");
}

bool DamageNumUI::Check_Number()
{
	Vec2 vFontLeftTop = m_vPos + m_vFontSelOffset;
	for (int i = 0; i < 3; ++i)
	{
		if (m_vMousePos.x >= vFontLeftTop.x
			&& m_vMousePos.y >= vFontLeftTop.y
			&& m_vMousePos.x <= vFontLeftTop.x + 32.f
			&& m_vMousePos.y <= vFontLeftTop.y + 32.f)
		{
			SoundMgr::Play(L"Bt_Click");
			DamageNum::Select_DamageTex((size_t)i);
			return true;
		}

		vFontLeftTop.x += 72.f;
	}

	return false;
}

bool DamageNumUI::Check_Mode()
{
	Vec2 vModeLeftTop = m_vPos + m_vModeSelOffset;

	for (int i = 0; i < 2; ++i)
	{
		if (m_vMousePos.x >= vModeLeftTop.x
			&& m_vMousePos.y >= vModeLeftTop.y
			&& m_vMousePos.x <= vModeLeftTop.x + 40.f
			&& m_vMousePos.y <= vModeLeftTop.y + 24.f)
		{
			SoundMgr::Play(L"Bt_Click");
			DamageNum::Select_Option(Num_State(i));
			return true;
		}

		vModeLeftTop.x += 120.f;
	}

	return false;
}
