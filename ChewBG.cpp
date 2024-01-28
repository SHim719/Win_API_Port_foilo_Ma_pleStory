#include "ChewBG.h"
#include "ResourceMgr.h"


ChewBG::ChewBG()
{
}

ChewBG::~ChewBG()
{
}

void ChewBG::Initialize()
{
	m_vecBgTex.reserve(9);
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew1"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew2"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew3"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew4"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew5"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew6"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew7"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew8"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Chew9"));

	m_iMaxFrame = (UINT)m_vecBgTex.size();
	m_fFrameGap = 0.15f;
}
