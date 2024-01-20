#pragma once
#include "MovableUI.h"

class EquipUI;
class Item;

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

	bool KeyCheck() override { return KeyMgr::GetKeyDown(eKeyCode::I); }

	Item* GetPickingItem() const { return m_pPickingItem; }

	void Set_PickingItem_null();

	void SetEquipUI(EquipUI* ui) { m_equipUI = ui; }

	void SetSlotEmpty();
private:
	void initialize_InvenTab();
	void initialize_Slots();

	void check_focused();
	void check_moveTab();
	void check_InvenTab();
	void check_Slots();

	void render_InvenTab() const;
	void render_Slots() const;
	void render_Picking() const;
private:
	JoTexture* m_ButtonTex;

	Item* m_pPickingItem;

	EquipUI* m_equipUI;

	ItemType m_eFocused;

	Vec2 m_vArrButtonPos[(UINT)ItemType::IT_END];
	Vec2 m_vArrSlotPos[INVEN_MAX];

	UINT m_iButtonWidth;
	UINT m_iButtonHeight;
	UINT m_iSlotGapX;
	UINT m_iSlotGapY;
	UINT m_iPickingIdx;
};

