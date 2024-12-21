#include "GiantRootBG.h"
#include "ResourceMgr.h"

GiantRootBG::GiantRootBG()
{
}

GiantRootBG::~GiantRootBG()
{
}

void GiantRootBG::Initialize()
{
	m_vecBgTex.reserve(4);
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_GiantRoot1"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_GiantRoot2"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_GiantRoot3"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_GiantRoot4"));

	m_iMaxFrame = (UINT)m_vecBgTex.size();
	m_fFrameGap = 0.15f;
}


void GiantRootBG::Release()
{
}
