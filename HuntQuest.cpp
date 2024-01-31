#include "HuntQuest.h"
#include "RenderMgr.h"

void HuntQuest::Initialize()
{
	m_pMainTex = ResourceMgr::Find<JoTexture>(L"Hunt_Quest");
}

void HuntQuest::Render()
{
	RenderMgr::RenderImage(m_pMainTex,
		m_vPos.x, m_vPos.y
		, m_vPos.x + (float)m_pMainTex->GetWidth()
		, m_vPos.y + (float)m_pMainTex->GetHeight());

	string sHuntCount = to_string(m_iHuntCount);
	int size = (int)sHuntCount.size();

	for (int i = 0; i < size; ++i)
	{
		Vec2 vRenderPos = m_vPos + m_vNumberOffset[2 - i];

		RenderMgr::RenderFrame(m_pNumberTex,
			vRenderPos.x, vRenderPos.y
			, vRenderPos.x + 11.f
			, vRenderPos.y + 17.f
			, float(sHuntCount[size - i - 1] - '0') * 11.f, 0.f
			, float(sHuntCount[size - i - 1] - '0') * 11.f + 11.f, 17.f);
	}
}

void HuntQuest::Add_Hunt()
{
	if (m_bSatisfied)
		return;
	m_iHuntCount++;
	if (m_iHuntCount == m_iObjectives)
		m_bSatisfied = true;
		
}
