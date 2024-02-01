#include "StatUI.h"
#include "SoundMgr.h"
#include "PlayerStats.h"
#include "RenderMgr.h"
#include "UIMgr.h"


StatUI::StatUI()
	: m_pPlayerStats(nullptr)
	, m_pActiveButtonTex(nullptr)
	, m_pInActiveButtonTex(nullptr)
	, m_vec_BtRenderPos{}

{
}

StatUI::~StatUI()
{
}

void StatUI::Initialize()
{
	m_pMainTex = ResourceMgr::Load<JoTexture>(L"StatUI", L"Resources/UI/Status/StatUI.png");
	m_pActiveButtonTex = ResourceMgr::Find<JoTexture>(L"PointUpButton_Active");
	m_pInActiveButtonTex = ResourceMgr::Find<JoTexture>(L"PointUpButton_InActive");

	m_vPos = { 200.f, 300.f };

	Vec2 vButtonRenderPos = { 185.f, 226.f }; //244

	m_vec_BtRenderPos.reserve(4);
	for (size_t i = 0; i < 4; ++i)
	{
		Vec2 vRenderPos = vButtonRenderPos + Vec2(0.f, 18.f * (float)i);
		m_vec_BtRenderPos.push_back(vRenderPos);
	}

}

void StatUI::Update()
{
	m_vPrevMousePos = m_vMousePos;
	m_vMousePos = KeyMgr::GetMousePos();

	if (m_bIsMoving)
	{
		Vec2 vGap = m_vMousePos - m_vPrevMousePos;
		m_vPos += vGap;
	}

	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (UIMgr::IsMouseUsed() == false)
		{
			bool bFocused = Check_Focused();
			UIMgr::SetMouseUsed(bFocused);
			if (UIMgr::IsMouseUsed() == true)
			{
				Check_moveTab(23.f);
				Check_Buttons();
			}
		}
	}
	else if (KeyMgr::GetKeyUp(eKeyCode::LButton))
	{
		m_bIsMoving = false;
	}


}

void StatUI::LateUpdate()
{
}

void StatUI::Render()
{
	RenderMgr::RenderImage(m_pMainTex, m_vPos.x, m_vPos.y,
		m_vPos.x + m_pMainTex->GetWidth(), m_vPos.y + m_pMainTex->GetHeight());

	wstring wsStr = to_wstring(m_pPlayerStats->Get_Str() + m_pPlayerStats->Get_Extra_Str());
	if (m_pPlayerStats->Get_Extra_Str() > 0)
		wsStr += L" (" + wsStr + L"+ " + to_wstring(m_pPlayerStats->Get_Extra_Str()) + L")";
	wstring wsDex = to_wstring(m_pPlayerStats->Get_Dex() + m_pPlayerStats->Get_Extra_Dex());
	if (m_pPlayerStats->Get_Extra_Dex() > 0)
		wsDex += L" (" + wsDex + L"+ " + to_wstring(m_pPlayerStats->Get_Extra_Dex()) + L")";
	wstring wsInt = to_wstring(m_pPlayerStats->Get_Int() + m_pPlayerStats->Get_Extra_Int());
	if (m_pPlayerStats->Get_Extra_Int() > 0)
		wsInt += L" (" + wsInt + L"+ " + to_wstring(m_pPlayerStats->Get_Extra_Int()) + L")";
	wstring wsLuk = to_wstring(m_pPlayerStats->Get_Luk() + m_pPlayerStats->Get_Extra_Luk());
	if (m_pPlayerStats->Get_Extra_Luk() > 0)
		wsLuk += L" (" + wsLuk + L"+ " + to_wstring(m_pPlayerStats->Get_Extra_Luk()) + L")";

	wstring wsHp = to_wstring(m_pPlayerStats->Get_Hp()) + L" / " + to_wstring(m_pPlayerStats->Get_MaxHp());
	wstring wsMp = to_wstring(m_pPlayerStats->Get_Mp()) + L" / " + to_wstring(m_pPlayerStats->Get_MaxMp());


	// Info Render

	RenderMgr::RenderText(L"심재욱", m_vPos.x + 75.f, m_vPos.y + 29.f, m_vPos.x + 135.f, m_vPos.y + 45.f, 12.f, RGB(100, 100, 100));
	RenderMgr::RenderText(L"백수", m_vPos.x + 75.f, m_vPos.y + 48.f, m_vPos.x + 135.f, m_vPos.y + 62.f, 12.f, RGB(100, 100, 100));
	RenderMgr::RenderText(L"쥬신게임아카데미", m_vPos.x + 75.f, m_vPos.y + 66.f, m_vPos.x + 205.f, m_vPos.y + 80.f, 12.f, RGB(100, 100, 100));
	RenderMgr::RenderText(L"123456789", m_vPos.x + 75.f, m_vPos.y + 83.f, m_vPos.x + 205.f, m_vPos.y + 100.f, 12.f, RGB(100, 100, 100));

	RenderMgr::RenderText(wsHp, m_vPos.x + 75.f, m_vPos.y + 83.f + 17.f * 3.f + 3.f, m_vPos.x + 205.f, m_vPos.y + 83.f + 17.f * 4.f + 3.f, 12.f, RGB(100, 100, 100));
	RenderMgr::RenderText(wsMp, m_vPos.x + 75.f, m_vPos.y + 83.f + 17.f * 4.f + 4.f, m_vPos.x + 205.f, m_vPos.y + 83.f + 17.f * 5.f + 4.f, 12.f, RGB(100, 100, 100));

	RenderMgr::RenderText(wsStr, m_vPos.x + 75.f, m_vPos.y + 225.f, m_vPos.x + 180.f, m_vPos.y + 238.f, 12.f, RGB(100, 100, 100));
	RenderMgr::RenderText(wsDex, m_vPos.x + 75.f, m_vPos.y + 244.f, m_vPos.x + 180.f, m_vPos.y + 257.f, 12.f, RGB(100, 100, 100));
	RenderMgr::RenderText(wsInt, m_vPos.x + 75.f, m_vPos.y + 261.f, m_vPos.x + 180.f, m_vPos.y + 275.f, 12.f, RGB(100, 100, 100));
	RenderMgr::RenderText(wsLuk, m_vPos.x + 75.f, m_vPos.y + 280.f, m_vPos.x + 180.f, m_vPos.y + 293.f, 12.f, RGB(100, 100, 100));

	wstring wsStatPoint = to_wstring(m_pPlayerStats->Get_StatPoint());
	for (size_t i = 0; i < 3 - wsStatPoint.size(); ++i)
		wsStatPoint = L" " + wsStatPoint;

	RenderMgr::RenderText(wsStatPoint, m_vPos.x + 74.f, m_vPos.y + 198.f, m_vPos.x + 94.f, m_vPos.y + 212.f, 12.f, RGB(100, 100, 100));

	// Button Render
	JoTexture* pRenderTex = nullptr;
	if (m_pPlayerStats->Get_StatPoint() > 0)
		pRenderTex = m_pActiveButtonTex;
	else
		pRenderTex = m_pInActiveButtonTex;

	for (size_t i = 0; i < 4; ++i)
	{
		Vec2 vLeftTop = m_vPos + m_vec_BtRenderPos[i];
		RenderMgr::RenderImage(pRenderTex, vLeftTop.x, vLeftTop.y, vLeftTop.x + 14.f, vLeftTop.y + 12.f);
	}


}

void StatUI::Release()
{
}

void StatUI::OnInActive()
{
	SoundMgr::Play(L"CloseWindow"); 
}

void StatUI::OnActive()
{
	SoundMgr::Play(L"OpenWindow");
}

void StatUI::Check_Buttons()
{
	if (0 == m_pPlayerStats->Get_StatPoint()) return;

	for (size_t i = 0; i < m_vec_BtRenderPos.size(); ++i)
	{
		Vec2 vLeftTop = m_vPos + m_vec_BtRenderPos[i];

		if (m_vMousePos.x >= vLeftTop.x
			&& m_vMousePos.y >= vLeftTop.y
			&& m_vMousePos.x <= vLeftTop.x + 14.f
			&& m_vMousePos.y <= vLeftTop.y + 12.f)
		{
			
			SoundMgr::Play(L"Bt_Click");
			m_pPlayerStats->Add_StatPoint(-1);
			
			switch (eStatSequence(i))
			{
			case eStatSequence::STR:
				m_pPlayerStats->Add_Str(1);
				break;
			case eStatSequence::DEX:
				m_pPlayerStats->Add_Dex(1);
				break;
			case eStatSequence::INT:
				m_pPlayerStats->Add_Int(1);
				break;
			case eStatSequence::LUK:
				m_pPlayerStats->Add_Luk(1);
				break;
			}
			return;
		}

	}
}
