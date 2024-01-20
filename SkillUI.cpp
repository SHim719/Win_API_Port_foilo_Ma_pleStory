#include "SkillUI.h"
#include "SkillStats.h"
#include "RenderMgr.h"
#include "Enrollable.h"
#include "Skill.h"
#include "UIMgr.h"
#include "SoundMgr.h"


SkillUI::SkillUI()
	: m_pSkillStats(nullptr)
	, m_pActiveButtonTex(nullptr)
	, m_pInActiveButtonTex(nullptr)
	, m_vRemainOffset{}
	, m_pPicking(nullptr)
	, m_pQuickSlot(nullptr)
	, m_bThisFramePicking(false)
{
	SetName(L"SkillUI");
}

SkillUI::~SkillUI()
{
	Release();
}

void SkillUI::Initialize()
{
	m_vPos = { 600.f, 200.f }; 
	m_vRemainOffset = { 290.f, 31.f };

	m_pMainTex = ResourceMgr::Load<JoTexture>(L"SKillUI", L"Resources/UI/Skill/SkillUI.png");
	m_pActiveButtonTex = ResourceMgr::Load<JoTexture>(L"PointUpButton_Active", L"Resources/UI/Skill/up_active.png");
	m_pInActiveButtonTex = ResourceMgr::Load<JoTexture>(L"PointUpButton_InActive", L"Resources/UI/Skill/up_inactive.png");

	m_vecRenderInfo.reserve(SKILL_SLOT);

	Vec2 vBoxSize = { 140.f, 35.f };
	Vec2 vDefault_IconOffset = { 12.f, 91.f };
	Vec2 vDefault_SkillNameOffset = { 53.f, 93.f };
	Vec2 vDefault_PointOffset = { 53.f, 110.f };
	Vec2 vDefault_vButtonOffset = { 136.f , 110.f };

	UINT iCol = 2;

	Vec2 vGap = { 13.f, 6.f };

	//SKillbox 크기 140 35
	//xOffset 13.f yoffset 6.f;

	for (UINT i = 0; i < SKILL_SLOT; ++i)
	{
		RenderInfo tInfo;
		tInfo.vIconOffset = vDefault_IconOffset 
			+ Vec2((vBoxSize.x + vGap.x) * (i % iCol), (vBoxSize.y + vGap.y) * (i / iCol));
		tInfo.vSkillNameOffset = vDefault_SkillNameOffset
			+ Vec2((vBoxSize.x + vGap.x) * (i % iCol), (vBoxSize.y + vGap.y) * (i / iCol));
		tInfo.vPointOffSet = vDefault_PointOffset
			+ Vec2((vBoxSize.x + vGap.x) * (i % iCol), (vBoxSize.y + vGap.y) * (i / iCol));
		tInfo.vButtonOffSet = vDefault_vButtonOffset
			+ Vec2((vBoxSize.x + vGap.x) * (i % iCol), (vBoxSize.y + vGap.y) * (i / iCol));
		m_vecRenderInfo.push_back(tInfo);
	}

}

void SkillUI::Update()
{
	m_vPrevMousePos = m_vMousePos;
	m_vMousePos = KeyMgr::GetMousePos();
	m_bThisFramePicking = false;

	if (m_bIsMoving)
	{
		Vec2 vGap = m_vMousePos - m_vPrevMousePos;
		m_vPos += vGap;
	}

	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (UIMgr::IsMouseUsed() == false)
		{
			bool bFocused = Check_Focused();
			UIMgr::SetMouseUsed(bFocused);
			if (bFocused == true)
			{
				Check_moveTab(22.f);
				Check_Slots();
				Check_Button();
			}
		}
	}
	else if (KeyMgr::GetKeyUp(eKeyCode::LButton))
	{
		m_bIsMoving = false;
	}

}

void SkillUI::LateUpdate()
{
}

void SkillUI::Render()
{
	vector<Skill*>& vecSkills = m_pSkillStats->Get_vecSkills();

	RenderMgr::RenderImage(m_pMainTex, m_vPos.x, m_vPos.y,
		m_vPos.x + m_pMainTex->GetWidth(), m_vPos.y + m_pMainTex->GetHeight());

	for (size_t i = 0; i < vecSkills.size(); ++i)
	{
		const RenderInfo& renderInfo = m_vecRenderInfo[i];

		// 아이콘 렌더링
		JoTexture* pIconTex = (static_cast<Enrollable*>(vecSkills[i]))->GetIconTex();
		Vec2 vLeftTop = { m_vPos.x + renderInfo.vIconOffset.x, m_vPos.y + renderInfo.vIconOffset.y };
		Vec2 vRightBottom = vLeftTop + Vec2((float)pIconTex->GetWidth(), (float)pIconTex->GetHeight());

		RenderMgr::RenderImage(pIconTex,
			vLeftTop.x,
			vLeftTop.y,
			vRightBottom.x,
			vRightBottom.y);

		// 스킬 이름 렌더링
		const wstring& sSkillName = vecSkills[i]->GetName();
		vLeftTop = { m_vPos.x + renderInfo.vSkillNameOffset.x, m_vPos.y + renderInfo.vSkillNameOffset.y };
		RenderMgr::RenderText(sSkillName, vLeftTop.x, vLeftTop.y, vLeftTop.x + 100.f, vLeftTop.y + 10.f, 12.f,
			RGB(50, 50, 50));

		// 스킬 포인트 렌더링
		wstring sSkillPoint = to_wstring(vecSkills[i]->GetSkillPoint());
		vLeftTop = { m_vPos.x + renderInfo.vPointOffSet.x, m_vPos.y + renderInfo.vPointOffSet.y };
		RenderMgr::RenderText(sSkillPoint, vLeftTop.x, vLeftTop.y, vLeftTop.x + 20.f, vLeftTop.y + 10.f, 12.f,
			RGB(50, 50, 50));

		// up 버튼 렌더링
		vLeftTop = { m_vPos.x + renderInfo.vButtonOffSet.x, m_vPos.y + renderInfo.vButtonOffSet.y };
		vRightBottom = vLeftTop
			+ Vec2((float)m_pInActiveButtonTex->GetWidth(), (float)m_pInActiveButtonTex->GetHeight());

		JoTexture* pButtonTex = nullptr;
		if (m_pSkillStats->GetRemainingPoint())
			pButtonTex = m_pActiveButtonTex;
		else
			pButtonTex = m_pInActiveButtonTex;

		RenderMgr::RenderImage(pButtonTex,
			vLeftTop.x,
			vLeftTop.y,
			vRightBottom.x,
			vRightBottom.y);
	}

	// 우 상단 남은 스킬포인트 렌더링
	wstring wsRemainPoints = to_wstring(m_pSkillStats->GetRemainingPoint());
	RenderMgr::RenderText(wsRemainPoints
		, m_vPos.x + m_vRemainOffset.x
		, m_vPos.y + m_vRemainOffset.y
		, m_vPos.x + m_vRemainOffset.x + 20.f
		, m_vPos.y + m_vRemainOffset.y + 10.f
		, 12.f, RGB(50, 50, 50));

	// 마우스에 피킹된 스킬아이콘 렌더링
	if (m_pPicking)
	{
		RenderMgr::RenderImage(m_pPicking->GetIconTex(),
			m_vMousePos.x,
			m_vMousePos.y,
			m_vMousePos.x + 32.f,
			m_vMousePos.y + 32.f,
			0.5f);
	}

}

void SkillUI::Release()
{
}

void SkillUI::OnInActive()
{
	if (m_pPicking)
		m_pPicking = nullptr;

	SoundMgr::Play(L"CloseWindow");
}

void SkillUI::OnActive()
{
	SoundMgr::Play(L"OpenWindow");
}

void SkillUI::Check_Slots()
{
	float fIconWidth = 32.f;
	float fIconHeight = 32.f;
	vector<Skill*>& vecSkills = m_pSkillStats->Get_vecSkills();

	for (size_t i = 0; i < vecSkills.size(); ++i)
	{
		const RenderInfo& renderInfo = m_vecRenderInfo[i];
		Vec2 vLeftTop = { m_vPos.x + renderInfo.vIconOffset.x, m_vPos.y + renderInfo.vIconOffset.y };

		if (m_vMousePos.x >= vLeftTop.x
			&& m_vMousePos.y >= vLeftTop.y
			&& m_vMousePos.x <= vLeftTop.x + fIconWidth
			&& m_vMousePos.y <= vLeftTop.y + fIconHeight)
		{
			if (0 == vecSkills[i]->GetSkillPoint())
				return;

			// Picking Sound Play
			m_pPicking = vecSkills[i];
			m_bThisFramePicking = true;
		}
		
	}

}

void SkillUI::Check_Button()
{
	if (0 == m_pSkillStats->GetRemainingPoint()) return;

	vector<Skill*>& vecSkills = m_pSkillStats->Get_vecSkills();

	for (size_t i = 0; i < vecSkills.size(); ++i)
	{
		const RenderInfo& renderInfo = m_vecRenderInfo[i];
		Vec2 vLeftTop = { m_vPos.x + renderInfo.vButtonOffSet.x, m_vPos.y + renderInfo.vButtonOffSet.y };

		if (m_vMousePos.x >= vLeftTop.x
			&& m_vMousePos.y >= vLeftTop.y
			&& m_vMousePos.x <= vLeftTop.x + 14.f
			&& m_vMousePos.y <= vLeftTop.y + 12.f)
		{
			// StatsUp Sound Play
			m_pSkillStats->AddPoint(-1);
			if (!vecSkills[i]->IsMaxPoint())
			{
				vecSkills[i]->AddPoint();
				return;
			}
		}

	}
}
