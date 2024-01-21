#include "Item.h"

Item::Item(const ItemType& type)
	: m_pItemTex(nullptr)
	, m_eItemType(type)
	, m_iMaxCount(0)
	, m_iSellPrice(0)
{ 
}

Item::~Item()
{
}
