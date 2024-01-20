#pragma once
#include "MovableUI.h"
#include "Equipable.h"

class InvenUI;
class EquipStats;

class EquipUI :
    public MovableUI
{
public:
	EquipUI();
	~EquipUI();

	void Initialize()	override;
	void Update()		override;
	void Render()		override;
	void Release()		override;

	void OnActive()		override;
	void OnInActive()	override;

	bool KeyCheck() const { return KeyMgr::GetKeyDown(eKeyCode::E); }

	Item* GetPickingItem() const { return m_pPickingItem; };
	void Set_PickingItem_null();

	void SetInvenUI(InvenUI* _pInvenUI) { m_pInvenUI = _pInvenUI; }
	void SetEquipStats(EquipStats* _pEquipStats) { m_pEquipStats = _pEquipStats; }

	void UnEquip(const EquipType& type);
private:
	void initialize_SlotPos();

	void check_Slots();

	void render_Slots() const;
	void render_Picking() const;
private:
	EquipStats* m_pEquipStats;
	Item* m_pPickingItem;
	InvenUI* m_pInvenUI;
	Vec2 m_arrSlotPos[(UINT)EquipType::ET_END];
	bool m_bThisFramePicking
};

