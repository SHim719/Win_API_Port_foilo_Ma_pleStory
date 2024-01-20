#include "HudUI.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"

HudUI::HudUI()
	: m_pHpBarTex(nullptr)
	, m_pMpBarTex(nullptr)
	, m_vHpBarPos{}
	, m_vMpBarPos{}
{
	SetName(L"HudUI");
}

HudUI::~HudUI()
{
}

void HudUI::Initialize()
{
	m_pMainTex = ResourceMgr::Load<JoTexture>(L"MainBar", L"Resources/UI/MainBar/MainBar.png");
	m_pHpBarTex = ResourceMgr::Load<JoTexture>(L"HpBar", L"Resources/UI/MainBar/HpBar.png");
	m_pMpBarTex = ResourceMgr::Load<JoTexture>(L"MpBar", L"Resources/UI/MainBar/MpBar.png");

	m_vPos = { 400.f, 695.f };
	m_vHpBarPos = m_vPos + Vec2(25.f, 28.f);
	m_vMpBarPos = m_vPos + Vec2(25.f, 45.f);
}

void HudUI::Update()
{
}

void HudUI::LateUpdate()
{
}

void HudUI::Render()
{
	RenderMgr::RenderImage(m_pHpBarTex, m_vHpBarPos.x, m_vHpBarPos.y,
		m_vHpBarPos.x + m_pHpBarTex->GetWidth(), m_vHpBarPos.y + m_pHpBarTex->GetHeight());
	RenderMgr::RenderImage(m_pMpBarTex, m_vMpBarPos.x, m_vMpBarPos.y,
		m_vMpBarPos.x + m_pMpBarTex->GetWidth(), m_vMpBarPos.y + m_pMpBarTex->GetHeight());

	RenderMgr::RenderImage(m_pMainTex, m_vPos.x, m_vPos.y,
		m_vPos.x + m_pMainTex->GetWidth(), m_vPos.y + m_pMainTex->GetHeight());

}

void HudUI::Release()
{
}
