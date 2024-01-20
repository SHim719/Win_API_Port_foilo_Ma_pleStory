#include "Item.h"

Item::Item(const ItemType& type)
	: m_pItemTex(nullptr)
	, m_eItemType(type)
{ 
}

Item::~Item()
{
}
