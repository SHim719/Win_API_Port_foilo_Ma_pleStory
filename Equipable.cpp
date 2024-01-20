#include "Equipable.h"

Equipable::Equipable(const EquipType& type)
	: Item(ItemType::IT_EQUIPABLE)
	, m_eEquipType(type)
{
}

Equipable::~Equipable()
{
}
