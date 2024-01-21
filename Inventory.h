#pragma once

#include "CommonInclude.h"
#include "Item.h"


#define INVEN_MAX 24

struct Slot
{
	static Slot empty_Slot;
	Item* item;
	UINT iCount;

	void Clear()
	{
		item = nullptr;
		iCount = 0;
	}
};


class Inventory
{
public:
	Inventory();
	~Inventory();

	bool Insert_Item(Item* item, const UINT& count);
	Slot Insert_ItemToIdx(Item* item, const UINT& idx, const UINT& iCount);
	void Swap_Slot(const ItemType& type, const UINT& iLeft, const UINT& iRight);

	void SetSlotEmpty(const ItemType& tab, const UINT& idx) { m_arrInventory[(UINT)tab][idx].Clear(); }
	const Slot& GetSlot(const ItemType& type, const UINT& idx) { return m_arrInventory[(UINT)type][idx]; }

	void Add_Meso(const int& _iMeso) { m_iMeso += _iMeso; }
	const int& Get_Meso() const { return m_iMeso; }

	Slot* Get_Inventory(const UINT& _iType) { return m_arrInventory[_iType]; }
private:
	Slot m_arrInventory[(UINT)ItemType::IT_END][INVEN_MAX];

	int m_iMeso;
};

