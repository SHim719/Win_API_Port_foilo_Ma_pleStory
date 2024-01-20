#include "QuickSlotUI.h"
#include "QuickStats.h"
#include "RenderMgr.h"
#include "KeyMgr.h"
#include "UIMgr.h"
#include "SkillUI.h"
#include "Enrollable.h"

QuickSlotUI::QuickSlotUI()
	: m_vecRenderPos{}
	, m_pQuickStats(nullptr)
	, m_vecKeyTex{}
	, m_pSkillUI(nullptr)
	, m_pPicking(nullptr)
	, m_bThisFramePicking(false)
	, m_iNowPickingIdx(-1)
{
}

QuickSlotUI::~QuickSlotUI()
{
}

void QuickSlotUI::Initialize()
{
	m_pMainTex = ResourceMgr::Load<JoTexture>(L"QuickSlotUI", L"Resources/UI/QuickSlot/QuickSlotUI.png");
	m_vPos = { 810.f, 695.f };

	m_vecRenderPos.resize(SLOT_COUNT);
	m_vecKeyTex.resize(SLOT_COUNT);

	UINT iCol = 6;
	Vec2 vStartOffset = { 2.f , 1.f };
	Vec2 vGap = { 35.f, 35.f };

	for (int i = 0; i < SLOT_COUNT; ++i)
	{
		m_vecRenderPos[i] = vStartOffset + Vec2(vGap.x * (i % iCol), vGap.y * (i / iCol));
	}

	m_vecKeyTex[0] = ResourceMgr::Load<JoTexture>(L"Key_A", L"Resources/UI/QuickSlot/a.png");
	m_vecKeyTex[1] = ResourceMgr::Load<JoTexture>(L"Key_S", L"Resources/UI/QuickSlot/s.png");
	m_vecKeyTex[2] = ResourceMgr::Load<JoTexture>(L"Key_D", L"Resources/UI/QuickSlot/d.png");
	m_vecKeyTex[3] = ResourceMgr::Load<JoTexture>(L"Key_F", L"Resources/UI/QuickSlot/f.png");
	m_vecKeyTex[4] = ResourceMgr::Load<JoTexture>(L"Key_G", L"Resources/UI/QuickSlot/g.png");
	m_vecKeyTex[5] = ResourceMgr::Load<JoTexture>(L"Key_H", L"Resources/UI/QuickSlot/h.png");
	m_vecKeyTex[6] = ResourceMgr::Load<JoTexture>(L"Key_Ctrl", L"Resources/UI/QuickSlot/ctrl.png");
	m_vecKeyTex[7] = ResourceMgr::Load<JoTexture>(L"Key_Shift", L"Resources/UI/QuickSlot/shift.png");
	m_vecKeyTex[8] = ResourceMgr::Load<JoTexture>(L"Key_1", L"Resources/UI/QuickSlot/1.png");
	m_vecKeyTex[9] = ResourceMgr::Load<JoTexture>(L"Key_2", L"Resources/UI/QuickSlot/2.png");
	m_vecKeyTex[10] = ResourceMgr::Load<JoTexture>(L"Key_3", L"Resources/UI/QuickSlot/3.png");
	m_vecKeyTex[11] = ResourceMgr::Load<JoTexture>(L"Key_4", L"Resources/UI/QuickSlot/4.png");
}

void QuickSlotUI::Update()
{
	m_bThisFramePicking = false;
	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		if (!UIMgr::IsMouseUsed())
		{
			Check_Slots();
		}
		Set_Picking_null();
		m_pSkillUI->Set_Picking_null();
		// TODO: 소비아이템 피킹 null
	}
}

void QuickSlotUI::LateUpdate()
{
}

void QuickSlotUI::Render()
{
	RenderMgr::RenderImage(m_pMainTex, m_vPos.x, m_vPos.y,
		m_vPos.x + (float)m_pMainTex->GetWidth(), m_vPos.y + (float)m_pMainTex->GetHeight());

	const vector<Enrollable*>& vecEnroll = m_pQuickStats->GetEnrollState();

	for (size_t i = 0; i < SLOT_COUNT; ++i)
	{
		Vec2 vLeftTop = m_vPos + m_vecRenderPos[i];
		Vec2 vRightBottom = vLeftTop + Vec2((float)m_vecKeyTex[i]->GetWidth(), (float)m_vecKeyTex[i]->GetHeight());

		// 퀵슬롯 렌더링
		if (vecEnroll[i])
			vecEnroll[i]->Render(vLeftTop);

		RenderMgr::RenderImage(m_vecKeyTex[i],
			vLeftTop.x, vLeftTop.y,
			vRightBottom.x, vRightBottom.y);
	}

	// 마우스에 피킹된 스킬아이콘 렌더링
	if (m_pPicking)
	{
		Vec2 vMousePos = KeyMgr::GetMousePos();
		RenderMgr::RenderImage(m_pPicking->GetIconTex(),
			vMousePos.x,
			vMousePos.y,
			vMousePos.x + 32.f,
			vMousePos.y + 32.f,
			0.5f);
	}
}

void QuickSlotUI::Release()
{
}

void QuickSlotUI::Check_Slots()
{
	Vec2 vMousePos = KeyMgr::GetMousePos();
	for (size_t i = 0; i < SLOT_COUNT; ++i)
	{
		Vec2 vLeftTop = m_vPos + m_vecRenderPos[i];
		Vec2 vRightBottom = vLeftTop + Vec2(32.f, 32.f);

		if (vMousePos.x >= vLeftTop.x
			&& vMousePos.y >= vLeftTop.y
			&& vMousePos.x <= vRightBottom.x
			&& vMousePos.y <= vRightBottom.y)
		{
			Enrollable* pEnroll = m_pSkillUI->GetPicking();
			// TODO: 소비아이템 picking 가져오기
			if (pEnroll)
			{
				m_pQuickStats->Set_Enroll(i, pEnroll);
				return;
			}
			
			// Picking이 없고, 퀵슬롯에 무언가 있을경우.
			if (m_pQuickStats->GetEnrollState()[i] != nullptr && m_pPicking == nullptr)
			{
				// play select sound
				m_pPicking = m_pQuickStats->GetEnrollState()[i];
				m_iNowPickingIdx = (int)i;
				m_bThisFramePicking = true;
				return;
			}
			// 피킹 된 것을 퀵슬롯에 놓을경우
			else if (m_pPicking != nullptr) 
			{
				m_pQuickStats->Set_Enroll(i, m_pPicking);
				if (m_iNowPickingIdx != -1)
				{
					m_pQuickStats->Set_Enroll(m_iNowPickingIdx, nullptr);
					m_iNowPickingIdx = -1;
				}
				return;
			}

		}
	}
}
