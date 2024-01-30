#include "TotemBar.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "TimeMgr.h"
#include "joObject.h"
#include "PerfectEffect.h"
#include "GreatEffect.h"
#include "GoodEffect.h"

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

	m_fSwordSpeed = 1400.f;
	m_fDir = 1.f;

	m_vSwordLimit.x = m_vSwordPos.x;
	m_vSwordLimit.y = m_vSwordPos.x + 580.f;

	m_vRedGauge.y = m_vBarPos.y + 35.f;
	m_vLeftYellowGauge.y = m_vBarPos.y + 35.f;
	m_vRightYellowGauge.y = m_vBarPos.y + 35.f;

	m_vGaugeLimit.x = 91.f;
	m_vGaugeLimit.y = 530.f;

	m_fRedGaugeScale = 50.f;
	m_fYellowGaugeScale = 40.f;

	m_vEffectOffset = { 160.f, 0.f };

	Reset_Bar();
}

void TotemBar::Update()
{
	if (m_bWait)
		return;

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

	if (!m_bWait)
	{
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
}

int TotemBar::Check_Bar()
{
	int iReturnVal = 1;

	if (m_vLeftYellowGauge.x <= m_vSwordPos.x && m_vSwordPos.x < m_vLeftYellowGauge.x + m_fYellowGaugeScale
		|| m_vRightYellowGauge.x <= m_vSwordPos.x && m_vSwordPos.x < m_vRightYellowGauge.x + m_fYellowGaugeScale)
	{
		auto effect = Instantiate<GreatEffect>(eLayerType::LT_UI);
		effect->Set_TotemBar(this);
		effect->SetPos(m_vSwordPos + m_vEffectOffset);
		iReturnVal = 2;
	}
		
	
	if (m_vRedGauge.x <= m_vSwordPos.x && m_vSwordPos.x < m_vRedGauge.x + m_fRedGaugeScale)
	{
		auto effect = Instantiate<PerfectEffect>(eLayerType::LT_UI);
		effect->Set_TotemBar(this);
		effect->SetPos(m_vSwordPos + m_vEffectOffset);
		iReturnVal = 4;
	}
		
	
	if (iReturnVal == 1)
	{
		auto effect = Instantiate<GoodEffect>(eLayerType::LT_UI);
		effect->Set_TotemBar(this);
		effect->SetPos(m_vSwordPos + m_vEffectOffset);
	}

	m_bWait = true;

	return iReturnVal;
}

void TotemBar::Reset_Bar()
{
	m_vSwordPos.x = m_vSwordLimit.x;
	m_vLeftYellowGauge.x = m_vBarPos.x + float(rand() % int(m_vGaugeLimit.y - m_vGaugeLimit.x)) + m_vGaugeLimit.x;
	m_vRedGauge.x = m_vLeftYellowGauge.x + m_fYellowGaugeScale;
	m_vRightYellowGauge.x = m_vRedGauge.x + m_fRedGaugeScale;
}

void TotemBar::Set_Start()
{
	m_bWait = false;
	Reset_Bar();
}

