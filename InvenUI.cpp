#include "InvenUI.h"
#include "SoundMgr.h"
#include "RenderMgr.h"
#include "UIMgr.h"
#include "Equipable.h"
#include "EquipUI.h"

InvenUI::InvenUI()
	: m_pButtonTex(nullptr)
	, m_pPickingItem(nullptr)
	, m_eFocused(ItemType::IT_EQUIPABLE)
	, m_iButtonHeight(0)
	, m_iButtonWidth(0)
	, m_iSlotGapX(0)
	, m_iSlotGapY(0)
	, m_iPickingIdx(0)
	, m_pEquipUI(nullptr)
	, m_bThisFramePicking(false)
	, m_pInventory(nullptr)
	, m_iPickItemCount(0)
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

	m_vPos = Vec2(500.0f, 200.0f);

	initialize_InvenTab();
	initialize_Slots();
}

void InvenUI::Update()
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
	if (m_pPickingItem)
		m_pPickingItem = nullptr;

	SoundMgr::Play(L"CloseWindow");
}

void InvenUI::OnActive()
{
	SoundMgr::Play(L"OpenWindow");
}

void InvenUI::Set_PickingItem_null()
{
	if (m_pPickingItem && !m_bThisFramePicking)
		m_pPickingItem = nullptr;
}

void InvenUI::SetSlotEmpty()
{
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
						m_iPickItemCount = pickSlot.iCount;
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
					const EquipType& type = static_cast<Equipable*>(prevSlot.item)->GetEquipType();
					m_pEquipUI->UnEquip(type);

					if (prevSlot.item != nullptr)
					{
						SoundMgr::Play(L"Slot_Click");
						m_pPickingItem = prevSlot.item;
						m_iPickItemCount = 1;
						m_bThisFramePicking = true;
					}
					else
					{
						SoundMgr::Play(L"Released_Picked");
					}
				}
			}
			else
			{
				m_pInventory->Swap_Slot(m_eFocused, m_iPickingIdx, i);
				Set_PickingItem_null();
			}
			/*else if (InputMgr::IsDoubleClicked())
			{
				switch (m_pPickingItem->GetItemType())
				{
				case ItemType::IT_EQUIPABLE:
				{
					Equipable* equip = static_cast<Equipable*>(m_pPickingItem);
					EquipMgr::Equip((UINT)equip->GetEquipType(), m_pPickingItem);
					InventoryMgr::SetSlotEmpty(m_eFocused, i);
					Set_PickingItem_null();
					break;
				}
				case ItemType::IT_CONSUMABLE:
					break;
				default:
					break;
				}
			}*/
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
		if (item == nullptr) continue;

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
			// Render Number;
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
