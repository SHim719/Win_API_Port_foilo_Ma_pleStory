#include "DamageNum.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Camera.h"
#include "RenderMgr.h"
#include "joObject.h"

vector<JoTexture*> DamageNum::m_vecNormalDamageTex{};
vector<JoTexture*> DamageNum::m_vecCriDamageTex{};
size_t DamageNum::m_iIdx = 0;
Num_State DamageNum::m_eState = Num_State::Normal;

DamageNum::DamageNum()
	: m_pDamageTex(nullptr)
	, m_pCriticalTex(nullptr)
	, m_pPlayerDamageTex(nullptr)
	, m_bPlayerHit(false)
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
	m_pDamageTex = m_vecNormalDamageTex[m_iIdx];
	m_pCriticalTex = m_vecCriDamageTex[m_iIdx];
	m_pPlayerDamageTex = ResourceMgr::Find<JoTexture>(L"Damaged_Num");

	m_pRigidbody = new Rigidbody;
	m_pRigidbody->SetOwner(this);

	m_fSpeed = 30.f;
	m_fAlpha = 1.f;


	switch (m_eState)
	{
	case Num_State::Normal:
		m_pRigidbody->SetUseGravity(false);
		m_pRigidbody->SetVelocityY(-m_fSpeed);
		break;
	case Num_State::Physics:
		m_pRigidbody->SetUseGravity(true);
		m_pRigidbody->SetGravity({ 0.f, 800.f });
		m_pRigidbody->SetVelocity({ (rand() % 3 - 1) * 150.f, -500.f });
		break;
	default:
		break;
	}
}

void DamageNum::Update()
{
	m_fNowTime += TimeMgr::DeltaTime();

	m_pRigidbody->Update();

	m_fAlpha -= 0.5f * TimeMgr::DeltaTime();
	m_fAlpha = max(m_fAlpha, 0.0f);

	if (m_fNowTime >= 2.f)
		Destroy(this);
	
}

void DamageNum::Render()
{
	Vec2 vRenderPos = GetPos();
	vRenderPos = Camera::CalcRenderPos(vRenderPos);

	JoTexture* pDamageTex = GetDamageTex();

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

void DamageNum::Init_DamageTex()
{
	m_vecNormalDamageTex.push_back(ResourceMgr::Find<JoTexture>(L"Damage_Num"));
	m_vecNormalDamageTex.push_back(ResourceMgr::Find<JoTexture>(L"Damage_Num_2"));
	m_vecNormalDamageTex.push_back(ResourceMgr::Find<JoTexture>(L"Damage_Num_3"));
	m_vecCriDamageTex.push_back(ResourceMgr::Find<JoTexture>(L"Damage_Num_Critical"));
	m_vecCriDamageTex.push_back(ResourceMgr::Find<JoTexture>(L"Damage_Num_Critical_2"));
	m_vecCriDamageTex.push_back(ResourceMgr::Find<JoTexture>(L"Damage_Num_Critical_3"));

}

