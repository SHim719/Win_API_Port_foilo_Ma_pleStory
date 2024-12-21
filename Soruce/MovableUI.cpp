#include "MovableUI.h"
#include "UIMgr.h"

bool MovableUI::Check_Focused()
{
	float width = (float)m_pMainTex->GetWidth();
	float height = (float)m_pMainTex->GetHeight();
	if (m_vMousePos.x >= m_vPos.x
		&& m_vMousePos.y >= m_vPos.y
		&& m_vMousePos.x <= m_vPos.x + width
		&& m_vMousePos.y <= m_vPos.y + height)
	{
		return true;
	}
	return false;
}

void MovableUI::Check_moveTab(const float& _fHeight)
{
	float width = (float)m_pMainTex->GetWidth();
	float height = _fHeight;

	if (m_vMousePos.x >= m_vPos.x
		&& m_vMousePos.y >= m_vPos.y
		&& m_vMousePos.x <= m_vPos.x + width
		&& m_vMousePos.y <= m_vPos.y + height)
	{
		m_bIsMoving = true;
	}
}
