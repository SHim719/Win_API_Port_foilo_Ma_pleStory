#include "AnimBG.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Camera.h"
#include "RenderMgr.h"

AnimBG::AnimBG()
{
}

AnimBG::~AnimBG()
{
}

void AnimBG::Initialize()
{
	m_vecBgTex.reserve(16);

	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew1"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew2"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew3"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew4"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew5"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew6"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew7"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew8"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew9"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew10"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew11"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew12"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew13"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew14"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew15"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew16"));

	m_iMaxFrame = (UINT)m_vecBgTex.size();
}


void AnimBG::Update()
{
	m_fNowTime += TimeMgr::DeltaTime();
	if (m_fNowTime >= m_fFrameGap)
	{
		m_iNowFrame = (m_iNowFrame + 1) % m_iMaxFrame;
		m_fNowTime = 0.f;
	}
}

void AnimBG::LateUpdate()
{
}

void AnimBG::Render()
{
	float fWidth = Camera::GetCameraSize().x;
	float fHeight = Camera::GetCameraSize().y;

	Vec2 vLookAt = Camera::GetLookAt();

	Vec2 vLeftTop = {};
	vLeftTop.x = vLookAt.x - fWidth * 0.5f;
	vLeftTop.y = vLookAt.y - fHeight * 0.5f;

	Vec2 vRightBottom = {};
	vRightBottom.x = vLookAt.x + fWidth * 0.5f;
	vRightBottom.y = vLookAt.y + fHeight * 0.5f;


	RenderMgr::RenderFrame(m_vecBgTex[m_iNowFrame],
		0, 0, fWidth, fHeight,
		vLeftTop.x, vLeftTop.y,
		vRightBottom.x, vRightBottom.y
	);
}

void AnimBG::Release()
{
}
