#pragma once

#include "Equipable.h"

class EquipStats
{
public:
	EquipStats();
	~EquipStats();

	void Equip(Equipable* _pEquip);
	void UnEquip(const EquipType& type);

	Item* GetEquipItemFromSlot(const UINT& type) { return (Item*)m_pArrEquipped[type]; }

private:
	Equipable* m_pArrEquipped[(UINT)EquipType::ET_END];
};

