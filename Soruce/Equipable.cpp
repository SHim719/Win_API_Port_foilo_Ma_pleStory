#include "Equipable.h"

Equipable::Equipable(const EquipType& type)
	: Item(ItemType::IT_EQUIPABLE)
	, m_eEquipType(type)
	, m_tEquipInfo{}
{
	m_iMaxCount = 1;
	m_iSellPrice = 9999;
}

Equipable::~Equipable()
{
}
