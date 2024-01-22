#include "InvenUI.h"
#include "SoundMgr.h"
#include "RenderMgr.h"
#include "UIMgr.h"
#include "Equipable.h"
#include "EquipUI.h"
#include "TimeMgr.h"
#include "Consumable.h"

InvenUI::InvenUI()
	: m_pButtonTex(nullptr)
	, m_pNumTex(nullptr)
	, m_pPickingItem(nullptr)
	, m_eFocused(ItemType::IT_EQUIPABLE)
	, m_iButtonHeight(0)
	, m_iButtonWidth(0)
	, m_iSlotGapX(0)
	, m_iSlotGapY(0)
	, m_iPickingIdx(-1)
	, m_pEquipUI(nullptr)
	, m_bThisFramePicking(false)
	, m_pInventory(nullptr)
	, m_bDoubleClickStart(false)
	, m_fDoubleClickCheck(0.f)
	, m_bDoubleClicked(false)
{
	SetName(L"InvenUI");
}

InvenUI::~InvenUI()
{

}

void InvenUI::Initialize()
{
	m_pMainTex = ResourceMgr::Load<JoTexture>(L"Inventory", L"Resources/UI/Inventory/UI_inventory.png");
	m_pButtonTex = ResourceMgr::Load<JoTexture>(L"Inventory_button", L"Resources/UI/Inventory/UI_inventory_tab.png");
	m_pNumTex = ResourceMgr::Find<JoTexture>(L"Item_Number");
	Consumable::SetNumTex(m_pNumTex);

	m_vPos = Vec2(500.0f, 200.0f);

	initialize_InvenTab();
	initialize_Slots();
}

void InvenUI::Update()
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
				Check_moveTab(23.f);
				check_InvenTab();
				check_Slots();
			}
		}
	}
	else if (KeyMgr::GetKeyUp(eKeyCode::LButton))
	{
		m_bIsMoving = false;
	}

}

void InvenUI::Render()
{
	RenderMgr::RenderImage(m_pMainTex, m_vPos.x, m_vPos.y,
		m_vPos.x + m_pMainTex->GetWidth(), m_vPos.y + m_pMainTex->GetHeight());

	render_InvenTab();
	render_Slots();
	render_Picking();
}

void InvenUI::Release()
{
}

void InvenUI::OnInActive()
{
	Set_PickingItem_null();

	SoundMgr::Play(L"CloseWindow");
}

void InvenUI::OnActive()
{
	SoundMgr::Play(L"OpenWindow");
}

void InvenUI::Set_PickingItem_null()
{
	if (m_pPickingItem && !m_bThisFramePicking)
	{
		m_iPickingIdx = -1;
		m_pPickingItem = nullptr;
	}
		
}

void InvenUI::Picking_Slot_Empty()
{
	m_pInventory->SetSlotEmpty(m_eFocused, m_iPickingIdx);
}

void InvenUI::Insert_Item(Item* _pItem, UINT _iCount)
{
	if (m_pInventory)
		m_pInventory->Insert_Item(_pItem, _iCount);
}

void InvenUI::initialize_InvenTab()
{
	m_iButtonWidth = m_pButtonTex->GetWidth() / 5;
	m_iButtonHeight = 17;

	Vec2 vButtonPos = Vec2(9.0f, 28.0f);
	for (UINT i = 0; i < (UINT)ItemType::IT_END; ++i)
	{
		m_vArrButtonPos[i] = vButtonPos;
		vButtonPos.x += m_iButtonWidth + 1.0f;
	}
}

void InvenUI::initialize_Slots()
{
	m_iSlotGapX = 4;
	m_iSlotGapY = 3;

	for (UINT i = 0; i < INVEN_MAX; ++i)
	{
		UINT x = i % 4;
		UINT y = i / 4;

		Vec2 vSlotPos = Vec2(11.0f, 50.0f);
		vSlotPos.x += float((m_iSlotGapX + 32) * x);
		vSlotPos.y += float((m_iSlotGapY + 32) * y);
		m_vArrSlotPos[i] = vSlotPos;
	}
}

void InvenUI::check_InvenTab()
{
	for (UINT i = 0; i < (UINT)ItemType::IT_END; ++i)
	{
		Vec2 buttonPos = m_vPos + m_vArrButtonPos[i];

		if (m_vMousePos.x >= buttonPos.x
			&& m_vMousePos.y >= buttonPos.y
			&& m_vMousePos.x <= buttonPos.x + (float)m_iButtonWidth
			&& m_vMousePos.y <= buttonPos.y + (float)m_iButtonHeight)
		{
			m_eFocused = (ItemType)i;
			SoundMgr::Play(L"Tab_Click");
			return;
		}
	}
}

void InvenUI::check_Slots()
{
	for (UINT i = 0; i < INVEN_MAX; ++i)
	{
		Vec2 slotPos = m_vPos + m_vArrSlotPos[i];

		if (m_vMousePos.x >= slotPos.x
			&& m_vMousePos.y >= slotPos.y
			&& m_vMousePos.x <= slotPos.x + 32.0f
			&& m_vMousePos.y <= slotPos.y + 32.0f)
		{
			Check_DoubleClick();

			Item* pEquipPicking = m_pEquipUI->GetPickingItem();
			if (m_pPickingItem == nullptr)
			{
				// 집은 것이 아무 것도 없다.
				if (pEquipPicking == nullptr)
				{
					const Slot& pickSlot = m_pInventory->GetSlot(m_eFocused, i);
					if (pickSlot.iCount > 0)
					{
						SoundMgr::Play(L"Slot_Click");
						m_pPickingItem = pickSlot.item;
						m_iPickingIdx = i;
						m_bThisFramePicking = true;
					}

				}
				// 장비창에 집은 것이 있을 경우
				else
				{
					if (m_eFocused != ItemType::IT_EQUIPABLE)
						return;

					Slot prevSlot = m_pInventory->Insert_ItemToIdx(pEquipPicking, i, 1);
					const EquipType& type = static_cast<Equipable*>(pEquipPicking)->GetEquipType();
					m_pEquipUI->UnEquip(type);

					if (prevSlot.item != nullptr)
					{
						SoundMgr::Play(L"Slot_Click");
						m_pPickingItem = prevSlot.item;
						m_iPickingIdx = -1;
						m_bThisFramePicking = true;
					}
					else
					{
						SoundMgr::Play(L"Released_Picked");
						m_pEquipUI->Set_PickingItem_null();
					}
				}
			}
			// 더블클릭 했을경우 장착
			else if (m_bDoubleClicked)
			{
				switch (m_pPickingItem->GetItemType())
				{
				case ItemType::IT_EQUIPABLE:
				{
					Equipable* equip = static_cast<Equipable*>(m_pPickingItem);
					m_pEquipUI->Equip(equip);
					m_pInventory->SetSlotEmpty(m_eFocused, i);
					Set_PickingItem_null();
					break;
				}
				case ItemType::IT_CONSUMABLE:
					break;
				default:
					break;
				}
				SoundMgr::Play(L"Released_Picked");
			}
			else
			{
				SoundMgr::Play(L"Released_Picked");
				m_pInventory->Swap_Slot(m_eFocused, m_iPickingIdx, i);
				Set_PickingItem_null();
			}
			return;
		}
	}
}

void InvenUI::render_InvenTab() const
{
	Vec2 vMainPos = m_vPos;
	Vec2 sliceStartPos = Vec2(0, 2);
	for (UINT i = 0; i < (UINT)ItemType::IT_END; ++i)
	{
		int iActive = 0;
		if (static_cast<ItemType>(i) == m_eFocused)
			iActive = 1;

		Vec2 renderPos = vMainPos + m_vArrButtonPos[i];

		RenderMgr::RenderFrame(m_pButtonTex
			, renderPos.x
			, renderPos.y
			, renderPos.x + m_iButtonWidth
			, renderPos.y + m_iButtonHeight
			, sliceStartPos.x
			, sliceStartPos.y + (m_iButtonHeight * iActive)
			, sliceStartPos.x + m_iButtonWidth
			, sliceStartPos.y + (m_iButtonHeight * iActive) + m_iButtonHeight);

		sliceStartPos.x += m_iButtonWidth;
	}
}

void InvenUI::render_Slots() const
{
	if (nullptr == m_pInventory)
		return;

	Vec2 vMainPos = m_vPos;

	for (UINT i = 0; i < INVEN_MAX; ++i)
	{
		const Slot& slot = m_pInventory->GetSlot(m_eFocused, i);
		Item* item = slot.item;
		if (item == nullptr || slot.iCount == 0) continue;

		JoTexture* itemTex = item->GetItemTex();

		Vec2 renderPos = vMainPos + m_vArrSlotPos[i];

		RenderMgr::RenderImage(itemTex
			, renderPos.x
			, renderPos.y
			, renderPos.x + 32.f
			, renderPos.y + 32.f);

		if (m_eFocused == ItemType::IT_CONSUMABLE
			|| m_eFocused == ItemType::IT_ETC)
		{
			renderPos += { 0.f, 21.f};
			render_Number(renderPos, slot.iCount);
		}
	}
}

void InvenUI::render_Picking() const
{
	if (m_pPickingItem == nullptr) return;

	JoTexture* pItemTex = m_pPickingItem->GetItemTex();

	RenderMgr::RenderImage(pItemTex
		, m_vMousePos.x
		, m_vMousePos.y
		, m_vMousePos.x + 32
		, m_vMousePos.y + 32
		, 0.5f);
}

void InvenUI::render_Number(Vec2 vLeftTop, const UINT& iNum) const
{
	string sNum = format("{}", iNum);//to_string(iNum);

	for (size_t i = 0; i < sNum.size(); ++i)
	{
		int iNum = sNum[i] - '0';

		RenderMgr::RenderFrame(m_pNumTex
			, vLeftTop.x, vLeftTop.y
			, vLeftTop.x + 8.f, vLeftTop.y + 11.f
			, 8.f * iNum, 0.f
			, 8.f * iNum + 8.f, 11.f);
		if (iNum == 1)
			vLeftTop.x += 5.f;
		else
			vLeftTop.x += 8.f;
	}
	
}

void InvenUI::Check_DoubleClick()
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
