#include "EquipUI.h"
#include "SoundMgr.h"
#include "EquipStats.h"
#include "RenderMgr.h"
#include "UIMgr.h"
#include "InvenUI.h"
#include "TimeMgr.h"

EquipUI::EquipUI()
	: m_pPickingItem(nullptr)
	, m_pInvenUI(nullptr)
	, m_pEquipStats(nullptr)
	, m_bThisFramePicking(false)
	, m_bDoubleClickStart(false)
	, m_fDoubleClickCheck(false)
	, m_bDoubleClicked(false)
{
	SetName(L"EquipUI");
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
	if (m_vPrevMousePos != m_vMousePos)
	{
		m_vPrevMousePos = m_vMousePos;
		m_bDoubleClickStart = false;
	}

	m_vMousePos = KeyMgr::GetMousePos();
	m_bThisFramePicking = false;
	m_bDoubleClicked = false;

	if (m_bDoubleClickStart)
	{
		m_fDoubleClickCheck += TimeMgr::DeltaTime();
	}

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
			if (UIMgr::IsMouseUsed() == true)
			{
				Check_moveTab(18.0f);
				check_Slots();
			}

			Item* pInvenPicking = m_pInvenUI->GetPickingItem();
			if (pInvenPicking != nullptr && dynamic_cast<Equipable*>(pInvenPicking))
				m_pInvenUI->Set_PickingItem_null();
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

void EquipUI::Equip(Equipable* const pEquip)
{
	if (m_pEquipStats)
		m_pEquipStats->Equip(pEquip);
}

void EquipUI::UnEquip(const EquipType& type)
{
	if (m_pEquipStats)
		m_pEquipStats->UnEquip(type);
}

void EquipUI::initialize_SlotPos()
{
	m_arrSlotPos[(UINT)EquipType::ET_HEAD] = Vec2(100.0f, 50.0f);
	m_arrSlotPos[(UINT)EquipType::ET_TOP] = Vec2(100.0f, 175.0f);
	m_arrSlotPos[(UINT)EquipType::ET_BOTTOM] = Vec2(100.0f, 218.0f);
	m_arrSlotPos[(UINT)EquipType::ET_SHOES] = Vec2(100.0f, 257.0f);
	m_arrSlotPos[(UINT)EquipType::ET_WEAPON] = Vec2(59.0f, 177.0f);
}

void EquipUI::check_Slots() 
{
	Vec2 pos = m_vPos;

	for (UINT i = 0; i < (UINT)EquipType::ET_END; ++i)
	{
		const Vec2& slotPos = pos + m_arrSlotPos[i];

		if (m_vMousePos.x >= slotPos.x
			&& m_vMousePos.y >= slotPos.y
			&& m_vMousePos.x <= slotPos.x + 32.0f
			&& m_vMousePos.y <= slotPos.y + 32.0f)
		{
			Check_DoubleClick();

			Item* pInvenPicking = m_pInvenUI->GetPickingItem();

			if (m_pPickingItem == nullptr)
			{
				// 집은 것이 하나도 없다.
				if (pInvenPicking == nullptr)
				{
					SoundMgr::Play(L"Slot_Click");
					m_pPickingItem = m_pEquipStats->GetEquipItemFromSlot(i);
					m_bThisFramePicking = true;
				}
				else // 인벤토리 UI에 집은 것이 있다.
				{
					Equipable* equip = dynamic_cast<Equipable*>(pInvenPicking);
					if (equip == nullptr || equip->GetEquipType() != (EquipType)i)
						return;
					SoundMgr::Play(L"Released_Picked");
					m_pEquipStats->Equip(equip);
					m_pInvenUI->Picking_Slot_Empty();
				}
			}
			else if (m_bDoubleClicked)
			{
				SoundMgr::Play(L"Released_Picked");
				Item* equipItem = m_pEquipStats->GetEquipItemFromSlot(i);
				m_pInvenUI->Insert_Item(equipItem, 1);
				m_pEquipStats->UnEquip((EquipType)i);
				Set_PickingItem_null();
			}
		}
	}
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

void EquipUI::Check_DoubleClick()
{
	if (!m_bDoubleClickStart)
	{
		m_bDoubleClickStart = true;
		return;
	}


	if (m_fDoubleClickCheck <= 1.f)
	{
		m_fDoubleClickCheck = 0.f;
		m_bDoubleClicked = true;
		m_bDoubleClickStart = false;
	}
	else
	{
		m_fDoubleClickCheck = 0.f;
		m_bDoubleClickStart = false;
	}
}

