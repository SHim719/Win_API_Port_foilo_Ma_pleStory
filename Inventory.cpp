#include "Inventory.h"

Inventory::Inventory()
	: m_arrInventory{}
{
}

Inventory::~Inventory()
{
}

bool Inventory::Insert_Item(Item* item, const UINT& count)
{
	return false;
}

Slot Inventory::Insert_ItemToIdx(Item* item, const UINT& idx, const UINT& iCount)
{
	if (item == nullptr)
		return;

	UINT type = (UINT)item->GetItemType();

	Slot& nowSlot = m_arrInventory[type][idx];

	if (nowSlot.item == nullptr)
	{
		nowSlot.item = item;
		nowSlot.iCount = iCount;
	}
	else if (nowSlot.item == item)
	{
		nowSlot.iCount += iCount;
		return nullptr;
	}
	else
	{
		Item* prevItem = nowSlot.item;
		nowSlot.item = item;
		return prevItem;
	}
	return nullptr;
}

void Inventory::Swap_Slot(const ItemType& type, const UINT& iLeft, const UINT& iRight)
{
}
