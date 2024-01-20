#include "EquipStats.h"

EquipStats::EquipStats()
	: m_pArrEquipped{}
{
}

EquipStats::~EquipStats()
{
}

void EquipStats::Equip(Equipable* _pEquip)
{
}

void EquipStats::UnEquip(const EquipType& type)
{
	m_pArrEquipped[(UINT)type] = nullptr;
}

