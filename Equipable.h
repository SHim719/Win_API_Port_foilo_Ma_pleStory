#pragma once
#include "Item.h"


enum class EquipType
{
	ET_HEAD,
	ET_TOP,
	ET_BOTTOM,
	ET_SHOES,
	ET_WEAPON,
	ET_END,
};

class Equipable :
    public Item
{
	Equipable(const EquipType& type);
	~Equipable();

	void Initialize() override {};

	void SetEquipType(const EquipType& type) { m_eEquipType = type; }
	const EquipType& GetEquipType() const { return m_eEquipType; }

private:
	EquipType m_eEquipType;
};

