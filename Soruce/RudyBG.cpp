#include "RudyBG.h"
#include "ResourceMgr.h"

void RudyBG::Initialize()
{
	m_vecBgTex.reserve(4);
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Rudy1"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Rudy2"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Rudy3"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Rudy4"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Rudy5"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Rudy6"));
	m_vecBgTex.push_back(ResourceMgr::Find<JoTexture>(L"BG_Rudy7"));

	m_iMaxFrame = (UINT)m_vecBgTex.size();
	m_fFrameGap = 0.18f;
}
