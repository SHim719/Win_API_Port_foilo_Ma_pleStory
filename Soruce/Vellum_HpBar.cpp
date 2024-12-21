#include "Vellum_HpBar.h"
#include "RenderMgr.h"
#include "ResourceMgr.h"
#include "Vellum.h"

Vellum_HpBar::Vellum_HpBar()
	: m_pMainTex(nullptr)
	, m_pHpBarTex(nullptr)
	, m_pVellum(nullptr)
	, m_bActive(false)
	, m_vHpRenderPos{}
{
}

Vellum_HpBar::~Vellum_HpBar()
{
}

void Vellum_HpBar::Initialize()
{
	m_pMainTex = ResourceMgr::Find<JoTexture>(L"Vellum_HpBar");
	m_pHpBarTex = ResourceMgr::Find<JoTexture>(L"Boss_Hp");
	
	SetPos({ 300.f, 0.f });
	m_vHpRenderPos = const_cast<Vec2&>(GetPos()) + Vec2(29.f, 3.f);
}


void Vellum_HpBar::Render()
{
	if (!m_bActive)
		return;

	float fRatio = (float)m_pVellum->GetHp() / (float)m_pVellum->GetMaxHp();

	Vec2 vRenderPos = GetPos();
	RenderMgr::RenderImage(m_pMainTex,
		vRenderPos.x, vRenderPos.y,
		vRenderPos.x + (float)m_pMainTex->GetWidth(), vRenderPos.y + (float)m_pMainTex->GetHeight());

	RenderMgr::RenderImage(m_pHpBarTex,
		m_vHpRenderPos.x, m_vHpRenderPos.y,
		m_vHpRenderPos.x + (float)m_pHpBarTex->GetWidth() * fRatio, m_vHpRenderPos.y + (float)m_pHpBarTex->GetHeight());

}
