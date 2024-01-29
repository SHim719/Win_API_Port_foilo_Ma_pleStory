#include "TotemBar.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "TimeMgr.h"


TotemBar::TotemBar()
{
}

TotemBar::~TotemBar()
{
}

void TotemBar::Initialize()
{
	m_pBarTex = ResourceMgr::Find<JoTexture>(L"Totem_Bar");
	m_pSwordTex = ResourceMgr::Find<JoTexture>(L"SwordIcon");
	m_pRedGaugeTex = ResourceMgr::Find<JoTexture>(L"Slash_RedGauge");
	m_pYellowGaugeTex = ResourceMgr::Find<JoTexture>(L"Slash_YellowGauge");

	m_vBarPos = { 166.f, 644.f };
	m_vSwordPos = m_vBarPos + Vec2(100.f, 15.f);

	m_fSwordSpeed = 900.f;
	m_fDir = 1.f;

	m_vSwordLimit.x = m_vSwordPos.x;
	m_vSwordLimit.y = m_vSwordPos.x + 580.f;

	m_vRedGauge.y = m_vBarPos.y + 35.f;
	m_vLeftYellowGauge.y = m_vBarPos.y + 35.f;
	m_vRightYellowGauge.y = m_vBarPos.y + 35.f;

	m_vGaugeLimit.x = 91.f;
	m_vGaugeLimit.y = 530.f;

	m_fRedGaugeScale = 45.f;
	m_fYellowGaugeScale = 35.f;

	m_vLeftYellowGauge.x = m_vBarPos.x + 105.f;
	m_vRedGauge.x = m_vLeftYellowGauge.x + m_fYellowGaugeScale;
	m_vRightYellowGauge.x = m_vRedGauge.x + m_fRedGaugeScale;
}

void TotemBar::Update()
{
	m_vSwordPos.x += m_fDir * m_fSwordSpeed * TimeMgr::DeltaTime();
	if (m_vSwordPos.x > m_vSwordLimit.y)
	{
		m_vSwordPos.x = m_vSwordLimit.y;
		m_fDir = -1.f;
	}
	else if (m_vSwordPos.x < m_vSwordLimit.x)
	{
		m_vSwordPos.x = m_vSwordLimit.x;
		m_fDir = 1.f;
	}
}

void TotemBar::LateUpdate()
{
}

void TotemBar::Render()
{
	RenderMgr::RenderImage(m_pBarTex
		, m_vBarPos.x, m_vBarPos.y
		, m_vBarPos.x + m_pBarTex->GetWidth(), m_vBarPos.y + m_pBarTex->GetHeight());

	RenderMgr::RenderImage(m_pYellowGaugeTex
		, m_vLeftYellowGauge.x
		, m_vLeftYellowGauge.y
		, m_vLeftYellowGauge.x + m_fYellowGaugeScale
		, m_vLeftYellowGauge.y + 40.f);

	RenderMgr::RenderImage(m_pRedGaugeTex
		, m_vRedGauge.x
		, m_vRedGauge.y
		, m_vRedGauge.x + m_fRedGaugeScale
		, m_vRedGauge.y + 40.f);

	RenderMgr::RenderImage(m_pYellowGaugeTex
		, m_vRightYellowGauge.x
		, m_vRightYellowGauge.y
		, m_vRightYellowGauge.x + m_fYellowGaugeScale
		, m_vRightYellowGauge.y + 40.f);

	RenderMgr::RenderImage(m_pSwordTex
		, m_vSwordPos.x - m_pSwordTex->GetWidth() * 0.5f, m_vSwordPos.y - m_pSwordTex->GetHeight() * 0.5f
		, m_vSwordPos.x + m_pSwordTex->GetWidth() * 0.5f, m_vSwordPos.y + m_pSwordTex->GetHeight() * 0.5f);

}
