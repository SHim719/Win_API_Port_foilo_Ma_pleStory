#include "AbyssCaveBG.h"
#include "ResourceMgr.h"

AbyssCaveBG::AbyssCaveBG()
{
}

AbyssCaveBG::~AbyssCaveBG()
{
}

void AbyssCaveBG::Initialize()
{
	m_vecBgTex.reserve(4);
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_AbyssCave1"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_AbyssCave2"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_AbyssCave3"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_AbyssCave4"));

	m_iMaxFrame = (UINT)m_vecBgTex.size();
	m_fFrameGap = 0.15f;
}
