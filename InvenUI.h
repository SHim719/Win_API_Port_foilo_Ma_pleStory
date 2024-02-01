#pragma once

#include "MovableUI.h"
#include "Inventory.h"

class EquipUI;

class InvenUI :
    public MovableUI
{
public:
	InvenUI();
	~InvenUI();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnInActive() override;
	void OnActive() override;

	bool KeyCheck() override { return KeyMgr::GetKeyDown(eKeyCode::I); }

	Item* GetPickingItem() const { return m_pPickingItem; }
	void Set_PickingItem_null();

	void SetEquipUI(EquipUI* ui) { m_pEquipUI = ui; }

	void SetInventory(Inventory* _pInven) { m_pInventory = _pInven; }

	void Picking_Slot_Empty();
	void Insert_Item(Item* _pItem, UINT _iCount);

	Slot* GetPickingSlot() 
	{ 
		if (m_iPickingIdx == -1) 
			return nullptr;
		return m_pInventory->GetSlotPtr(m_eFocused, m_iPickingIdx); 
	}
private:
	void initialize_InvenTab();
	void initialize_Slots();

	void check_InvenTab();
	void check_Slots();

	void render_InvenTab() const;
	void render_Slots() const;
	void render_Picking() const;
	void render_Number(Vec2 vLeftTop, const UINT& iNum) const;
	void render_Meso() const;

	void Check_DoubleClick();
private:
	Inventory* m_pInventory;

	JoTexture* m_pButtonTex;
	JoTexture* m_pNumTex;

	Item*	m_pPickingItem;
	bool	m_bThisFramePicking;

	EquipUI* m_pEquipUI;

	ItemType m_eFocused;

	Vec2 m_vArrButtonPos[(UINT)ItemType::IT_END];
	Vec2 m_vArrSlotPos[INVEN_MAX];

	UINT m_iButtonWidth;
	UINT m_iButtonHeight;
	UINT m_iSlotGapX;
	UINT m_iSlotGapY;
	int m_iPickingIdx;

	bool m_bDoubleClickStart;
	float m_fDoubleClickCheck;
	bool m_bDoubleClicked;
};

