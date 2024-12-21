#include "Button.h"
#include "KeyMgr.h"
#include "JoTexture.h"
#include "SoundMgr.h"
#include "RenderMgr.h"

Button::Button()
	: m_pButtonTex(nullptr)
	, m_pOnButtonTex(nullptr)
	, m_bOnButton(false)
{
}

Button::~Button()
{
}

void Button::Update()
{
	if (Check_Area())
	{
		if (KeyMgr::GetKeyDown(eKeyCode::LButton))
		{
			SoundMgr::Play(L"Bt_Click");
			Press_Button();
		}	
		else if (!m_bOnButton)
			m_bOnButton = true;
	}
	else
		m_bOnButton = false;


}

void Button::Render()
{
	JoTexture* pRenderTex = nullptr;
	if (m_bOnButton)
		pRenderTex = m_pOnButtonTex;
	else
		pRenderTex = m_pButtonTex;

	RenderMgr::RenderImage(pRenderTex
		, GetPos().x - pRenderTex->GetWidth() * 0.5f
		, GetPos().y - pRenderTex->GetHeight() * 0.5f
		, GetPos().x + pRenderTex->GetWidth() * 0.5f
		, GetPos().y + pRenderTex->GetHeight() * 0.5f);
}

bool Button::Check_Area()
{
	Vec2 vMousePos = KeyMgr::GetMousePos();

	if (vMousePos.x >= GetPos().x - m_pButtonTex->GetWidth() * 0.5f
		&& vMousePos.y >= GetPos().y - m_pButtonTex->GetHeight() * 0.5f
		&& vMousePos.x <= GetPos().x + m_pButtonTex->GetWidth() * 0.5f
		&& vMousePos.y <= GetPos().y + m_pButtonTex->GetHeight() * 0.5f)
	{
		return true;
	}

	return false;

	return false;
}
