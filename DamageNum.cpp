#include "DamageNum.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Camera.h"
#include "RenderMgr.h"
#include "joObject.h"

DamageNum::DamageNum()
	: m_pDamageTex(nullptr)
	, m_pCriticalTex(nullptr)
	, m_bCritical(false)
	, m_fNowTime(0.f)
	, m_fSpeed(0.f)
	, m_fAlpha(0.f)

{	   
}

DamageNum::~DamageNum()
{
}

void DamageNum::Initialize()
{
	m_pDamageTex = ResourceMgr::Find<JoTexture>(L"Damage_Num");
	m_pCriticalTex = ResourceMgr::Find<JoTexture>(L"Damage_Num_Critical");

	m_fSpeed = 30.f;
	m_fAlpha = 1.f;
}

void DamageNum::Update()
{
	m_fNowTime += TimeMgr::DeltaTime();

	m_tTransform.vPos.y -= m_fSpeed * TimeMgr::DeltaTime();

	m_fAlpha -= 0.5f * TimeMgr::DeltaTime();
	m_fAlpha = max(m_fAlpha, 0.0f);

	if (m_fNowTime >= 2.f)
		Destroy(this);
	
}

void DamageNum::Render()
{
	Vec2 vRenderPos = GetPos();
	vRenderPos = Camera::CalcRenderPos(vRenderPos);

	JoTexture* pDamageTex = nullptr;
	if (IsCritical())
		pDamageTex = m_pDamageTex;
	else
		pDamageTex = m_pCriticalTex;

	float fWidth = (float)pDamageTex->GetWidth() / 10.f;
	float fHeight = (float)pDamageTex->GetHeight();

	UINT iSize = (UINT)m_vecRenderNum.size();

	float fXSize = fWidth * (float)iSize;

	Vec2 vLeftTop = Vec2(vRenderPos.x - fXSize * 0.5f, vRenderPos.y);
	
	for (UINT i = 0; i < iSize; ++i)
	{
		float fYOffset = 3.f;
		if (i % 2 == 0)
			fYOffset *= -1.f;

		float fRenderNum = (float)m_vecRenderNum[i];
		Vec2 vRightBottom = vLeftTop + Vec2(fWidth, fHeight);

		RenderMgr::RenderFrame(pDamageTex
			, vLeftTop.x, vLeftTop.y + fYOffset
			, vRightBottom.x, vRightBottom.y + fYOffset
			, fWidth * fRenderNum, 0.f
			, fWidth * (fRenderNum + 1.f), fHeight
			, m_fAlpha);

		vLeftTop.x += fWidth - 12.f;
	}
}

void DamageNum::Init_Number(const string& _sNum)
{
	size_t sNumSize = _sNum.size();
	m_vecRenderNum.reserve(sNumSize);

	for (size_t i = 0; i < sNumSize; ++i)
		m_vecRenderNum.push_back(_sNum[i] - '0');
	
}
