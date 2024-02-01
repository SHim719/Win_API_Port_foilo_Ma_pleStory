#include "HudUI.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "PlayerStats.h"
#include "TimeMgr.h"

HudUI::HudUI()
	: m_pHpBarTex(nullptr)
	, m_pMpBarTex(nullptr)
	, m_pExpBarTex(nullptr)
	, m_pExpBarMaxTex(nullptr)
	, m_pLevelTex(nullptr)
	, m_vHpBarPos{}
	, m_vMpBarPos{}
	, m_pPlayerStats(nullptr)
	, m_fRenderHp(0.f)
	, m_fRenderMp(0.f)
	, m_fNowHp(0.f)
	, m_fNowMp(0.f)
	, m_fExpSpeed(0.f)
	, m_vExpBarPos{}
	, m_vLevelPos{}
	, m_sNowLevel("")
	, m_iNowLevel(0)
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
	m_pExpBarTex = ResourceMgr::Load<JoTexture>(L"ExpBarTex", L"Resources/UI/MainBar/ExpBar.png");
	m_pExpBarMaxTex = ResourceMgr::Load<JoTexture>(L"ExpBarMaxTex", L"Resources/UI/MainBar/ExpMaxBar.png");
	m_pLevelTex = ResourceMgr::Load<JoTexture>(L"LevelNum", L"Resources/UI/MainBar/Level_Num.png");
		
	m_vPos = { 400.f, 675.f };
	m_vHpBarPos = m_vPos + Vec2(25.f, 28.f);
	m_vMpBarPos = m_vPos + Vec2(25.f, 45.f);

	m_vExpBarPos = { 0.f, 758.f };
	m_vLevelPos = { 42.f, 8.f };
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
		m_fMpSpeed = fabs(m_fNowMp - m_fRenderMp) / 0.3f;
	}
	
	if (m_fNowExp != (float)m_pPlayerStats->Get_Exp())
	{
		m_fNowExp = (float)m_pPlayerStats->Get_Exp();
		m_fExpSpeed = fabs(m_fNowExp - m_fRenderExp) / 0.3f;
	}

	if (m_iNowLevel != m_pPlayerStats->Get_Level())
	{
		m_iNowLevel = m_pPlayerStats->Get_Level();
		m_sNowLevel = to_string(m_iNowLevel);
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

	if (m_fRenderExp < m_fNowExp)
	{
		m_fRenderExp += m_fExpSpeed * TimeMgr::DeltaTime();
		m_fRenderExp = min(m_fRenderExp, m_fNowExp);
	}
	else if (m_fRenderExp > m_fNowExp)
	{
		m_fRenderExp -= m_fExpSpeed * TimeMgr::DeltaTime();
		m_fRenderExp = max(m_fRenderExp, m_fNowExp);
	}

	float fHpRatio = m_fRenderHp / (float)m_pPlayerStats->Get_MaxHp();
	float fMpRatio = m_fRenderMp / (float)m_pPlayerStats->Get_MaxMp();
	float fExpRatio = m_fRenderExp / (float)m_pPlayerStats->Get_MaxExp();

	RenderMgr::RenderImage(m_pHpBarTex, m_vHpBarPos.x, m_vHpBarPos.y,
		m_vHpBarPos.x + (m_pHpBarTex->GetWidth() * fHpRatio), m_vHpBarPos.y + m_pHpBarTex->GetHeight());
	RenderMgr::RenderImage(m_pMpBarTex, m_vMpBarPos.x, m_vMpBarPos.y,
		m_vMpBarPos.x + (m_pMpBarTex->GetWidth() * fMpRatio), m_vMpBarPos.y + m_pMpBarTex->GetHeight());

	RenderMgr::RenderImage(m_pMainTex, m_vPos.x, m_vPos.y,
		m_vPos.x + m_pMainTex->GetWidth(), m_vPos.y + m_pMainTex->GetHeight());

	render_level();
	
	RenderMgr::RenderImage(m_pExpBarTex, m_vExpBarPos.x, m_vExpBarPos.y,
		m_vExpBarPos.x + 1024.f, m_vExpBarPos.y + 10.f);

	RenderMgr::RenderImage(m_pExpBarMaxTex, m_vExpBarPos.x + 15.f, m_vExpBarPos.y + 2,
		m_vExpBarPos.x + 15.f + (1009.f * fExpRatio), m_vExpBarPos.y + 9.f);

	
	render_level();
}

void HudUI::Release()
{
}

void HudUI::render_level()
{
	Vec2 vRenderPos = m_vPos + m_vLevelPos;
	for (size_t i = 0; i < m_sNowLevel.size(); ++i)
	{
		RenderMgr::RenderFrame(m_pLevelTex
			, vRenderPos.x, vRenderPos.y
			, vRenderPos.x + 7.f, vRenderPos.y + 10.f
			, (m_sNowLevel[i] - '0') * 7.f, 0.f
			, (m_sNowLevel[i] - '0') * 7.f + 7.f, 10.f);
		vRenderPos.x += 2.f;
	}
}
