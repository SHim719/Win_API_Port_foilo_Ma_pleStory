#pragma once

#include "Equipable.h"

class PlayerStats;

class EquipStats
{
public:
	EquipStats();
	~EquipStats();

	void Equip(Equipable* _pEquip);
	void UnEquip(const EquipType& type);

	Item* GetEquipItemFromSlot(const UINT& type) { return (Item*)m_pArrEquipped[type]; }

	void Set_PlayerStats(PlayerStats* const _stats) { m_pPlayerStats = _stats; }
private:
	Equipable* m_pArrEquipped[(UINT)EquipType::ET_END];
	PlayerStats* m_pPlayerStats;
};

