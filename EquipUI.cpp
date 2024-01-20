#include "EquipUI.h"
#include "SoundMgr.h"
#include "EquipStats.h"
#include "RenderMgr.h"
#include "UIMgr.h"

EquipUI::EquipUI()
	: m_pPickingItem(nullptr)
	, m_pInvenUI(nullptr)
	, m_pEquipStats(nullptr)
	, m_bThisFramePicking(false)
{
}

EquipUI::~EquipUI()
{
}

void EquipUI::Initialize()
{
	m_pMainTex = ResourceMgr::Load<JoTexture>(L"Equipment", L"Resources/UI/Equip/Equipment.png");

	m_vPos = Vec2(200.0f, 250.0f);

	initialize_SlotPos();
}

void EquipUI::Update()
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
			Check_Focused();
			if (UIMgr::IsMouseUsed() == true)
			{
				Check_moveTab(18.0f);
				check_Slots();
			}
		}
	}
	else if (KeyMgr::GetKeyUp(eKeyCode::LButton))
	{
		m_bIsMoving = false;
	}

}

void EquipUI::Render()
{
	RenderMgr::RenderImage(m_pMainTex
		, m_vPos.x
		, m_vPos.y
		, m_vPos.x + m_pMainTex->GetWidth()
		, m_vPos.y + m_pMainTex->GetHeight()
	);

	render_Slots();
	render_Picking();
}

void EquipUI::Release()
{
}

void EquipUI::OnActive()
{
	SoundMgr::Play(L"OpenWindow");
}

void EquipUI::OnInActive()
{
	if (m_pPickingItem)
		m_pPickingItem = nullptr;

	SoundMgr::Play(L"CloseWindow");
}

void EquipUI::Set_PickingItem_null()
{
	if (m_pPickingItem && !m_bThisFramePicking)
		m_pPickingItem = nullptr;
}

void EquipUI::UnEquip(const EquipType& type)
{
	if (m_pEquipStats)
		m_pEquipStats->UnEquip(type);
}

void EquipUI::initialize_SlotPos()
{
}

void EquipUI::check_Slots()
{
}

void EquipUI::render_Slots() const
{
	Vec2 pos = m_vPos;
	for (UINT i = 0; i < (UINT)EquipType::ET_END; ++i)
	{
		Item* pItem = m_pEquipStats->GetEquipItemFromSlot(i);
		if (pItem == nullptr) continue;

		JoTexture* pItemTex = pItem->GetItemTex();

		Vec2 renderPos = pos + m_arrSlotPos[i];

		RenderMgr::RenderImage(pItemTex
			, renderPos.x
			, renderPos.y
			, renderPos.x + 32.f
			, renderPos.y + 32.f
		);
	}
}

void EquipUI::render_Picking() const
{
	if (m_pPickingItem == nullptr) return;

	JoTexture* pItemTex = m_pPickingItem->GetItemTex();

	RenderMgr::RenderImage(pItemTex
		, m_vMousePos.x
		, m_vMousePos.y
		, m_vMousePos.x + 32.f
		, m_vMousePos.y + 32.f
		, 0.5f);
}
}
