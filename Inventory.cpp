#include "Inventory.h"

Slot Slot::empty_Slot = { nullptr, 0 };

Inventory::Inventory()
	: m_arrInventory{}
	, m_iMeso(500000)
{
}

Inventory::~Inventory()
{
}

bool Inventory::Insert_Item(Item* item, const UINT& count)
{
	if (item == nullptr)
		return false;

	UINT type = (UINT)item->GetItemType();
	UINT iMaxCount = item->GetMaxCount();

	for (Slot& slot : m_arrInventory[type])
	{
		if (slot.item == nullptr)
		{
			slot.item = item;
			slot.iCount = count;
			return true;
		}
		else if (slot.item == item && slot.iCount < iMaxCount)
		{
			slot.iCount += count;
			return true;
		}
	}

	return false;
}

Slot Inventory::Insert_ItemToIdx(Item* item, const UINT& idx, const UINT& iCount)
{
	if (item == nullptr)
		return Slot::empty_Slot;

	UINT type = (UINT)item->GetItemType();

	Slot& nowSlot = m_arrInventory[type][idx];
	Slot returnSlot = nowSlot;

	if (nowSlot.item == nullptr)
	{
		nowSlot.item = item;
		nowSlot.iCount = iCount;
	}
	else if (nowSlot.item == item || item->GetItemType() != ItemType::IT_EQUIPABLE)
	{
		nowSlot.iCount += iCount;
	}

	return returnSlot;
}

void Inventory::Swap_Slot(const ItemType& type, const UINT& iLeft, const UINT& iRight)
{
	UINT iType = (UINT)type;
	swap(m_arrInventory[iType][iLeft], m_arrInventory[iType][iRight]);
}
