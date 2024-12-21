#include "MiniMap.h"
#include "RenderMgr.h"
#include "JoTexture.h"

JoTexture* MiniMap::m_pPlayerIconTex = nullptr;
GameObject* MiniMap::m_pTarget = nullptr;

MiniMap::MiniMap()
	: m_pMiniMapTex(nullptr)
	, m_vLeftTop{}
	, m_vSize{}
	, m_vRealMapSize{}
{	   
}

MiniMap::~MiniMap()
{
}


void MiniMap::Render()
{
	RenderMgr::RenderImage(m_pMiniMapTex,
		0.f, 0.f,
		(float)m_pMiniMapTex->GetWidth(), (float)m_pMiniMapTex->GetHeight());

	Vec2 vRatio = const_cast<Vec2&>(m_pTarget->GetPos()) / m_vRealMapSize;
	Vec2 vRenderPos = m_vLeftTop + m_vSize * vRatio;

	RenderMgr::RenderImage(m_pPlayerIconTex
		, vRenderPos.x - m_pPlayerIconTex->GetWidth() * 0.5f, vRenderPos.y - m_pPlayerIconTex->GetHeight() * 0.5f
		, vRenderPos.x + m_pPlayerIconTex->GetWidth() * 0.5f, vRenderPos.y + m_pPlayerIconTex->GetHeight() * 0.5f);
}
