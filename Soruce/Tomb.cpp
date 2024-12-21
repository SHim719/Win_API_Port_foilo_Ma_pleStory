#include "Tomb.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "Camera.h"
#include "Player.h"
#include "joObject.h"


void Tomb::Initialize()
{
	m_pTombTex = ResourceMgr::Find<JoTexture>(L"Tomb");
}

void Tomb::Update()
{
	if (m_pPlayer)
	{
		if (!m_pPlayer->isDeadState())
			Destroy(this);
	}
}

void Tomb::Render()
{
	Vec2 vRenderPos = GetPos();
	Vec2 vOffset = Vec2(-20.f, -20.f);
	vRenderPos = Camera::CalcRenderPos(vRenderPos) + vOffset;

	RenderMgr::RenderImage(m_pTombTex
		, vRenderPos.x, vRenderPos.y 
		, vRenderPos.x + m_pTombTex->GetWidth()
		, vRenderPos.y + m_pTombTex->GetHeight());
}

