#include "HudUI.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "PlayerStats.h"
#include "TimeMgr.h"

HudUI::HudUI()
	: m_pHpBarTex(nullptr)
	, m_pMpBarTex(nullptr)
	, m_vHpBarPos{}
	, m_vMpBarPos{}
	, m_pPlayerStats(nullptr)
	, m_fRenderHp(0.f)
	, m_fRenderMp(0.f)
	, m_fNowHp(0.f)
	, m_fNowMp(0.f)
	//, m_fSpeed(0.f)
{
	SetName(L"HudUI");
}

HudUI::~HudUI()
{
}

void HudUI::Initialize()
{
	m_pMainTex = ResourceMgr::Load<JoTexture>(L"MainBar", L"Resources/UI/MainBar/MainBar.png");
	m_pHpBarTex = ResourceMgr::Load<JoTexture>(L"HpBar", L"Resources/UI/MainBar/HpBar.png");
	m_pMpBarTex = ResourceMgr::Load<JoTexture>(L"MpBar", L"Resources/UI/MainBar/MpBar.png");

	m_vPos = { 400.f, 695.f };
	m_vHpBarPos = m_vPos + Vec2(25.f, 28.f);
	m_vMpBarPos = m_vPos + Vec2(25.f, 45.f);

}

void HudUI::Update()
{
	if (m_fNowHp != (float)m_pPlayerStats->Get_Hp())
	{
		m_fNowHp = (float)m_pPlayerStats->Get_Hp();
		m_fHpSpeed = fabs(m_fNowHp - m_fRenderHp) / 0.3f;
	}

	if (m_fNowMp != (float)m_pPlayerStats->Get_Mp())
	{
		m_fNowMp = (float)m_pPlayerStats->Get_Mp();
		m_fMpSpeed = fabs(m_fNowHp - m_fRenderMp) / 0.3f;
	}
	

}

void HudUI::LateUpdate()
{
}

void HudUI::Render()
{
	if (m_fRenderHp < m_fNowHp)
	{
		m_fRenderHp += m_fHpSpeed * TimeMgr::DeltaTime();
		m_fRenderHp = min(m_fRenderHp, m_fNowHp);
	}
	else if (m_fRenderHp > m_fNowHp)
	{
		m_fRenderHp -= m_fHpSpeed * TimeMgr::DeltaTime();
		m_fRenderHp = max(m_fRenderHp, m_fNowHp);
	}

	if (m_fRenderMp < m_fNowMp)
	{
		m_fRenderMp += m_fMpSpeed * TimeMgr::DeltaTime();
		m_fRenderMp = min(m_fRenderMp, m_fNowMp);
	}
	else if (m_fRenderMp > m_fNowMp)
	{
		m_fRenderMp -= m_fMpSpeed * TimeMgr::DeltaTime();
		m_fRenderMp = max(m_fRenderMp, m_fNowMp);
	}

	float fHpRatio = m_fRenderHp / (float)m_pPlayerStats->Get_MaxHp();
	float fMpRatio = m_fRenderMp / (float)m_pPlayerStats->Get_MaxMp();

	RenderMgr::RenderImage(m_pHpBarTex, m_vHpBarPos.x, m_vHpBarPos.y,
		m_vHpBarPos.x + (m_pHpBarTex->GetWidth() * fHpRatio), m_vHpBarPos.y + m_pHpBarTex->GetHeight());
	RenderMgr::RenderImage(m_pMpBarTex, m_vMpBarPos.x, m_vMpBarPos.y,
		m_vMpBarPos.x + (m_pMpBarTex->GetWidth() * fMpRatio), m_vMpBarPos.y + m_pMpBarTex->GetHeight());

	RenderMgr::RenderImage(m_pMainTex, m_vPos.x, m_vPos.y,
		m_vPos.x + m_pMainTex->GetWidth(), m_vPos.y + m_pMainTex->GetHeight());

}

void HudUI::Release()
{
}
