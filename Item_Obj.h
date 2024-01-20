#pragma once
#include "GameObject.h"

class Item;

class Item_Obj :
    public GameObject
{
public:
    Item_Obj();
    ~Item_Obj();

    void SetItem(Item* const _pItem) { m_pItem = _pItem; }
    void SetCount(const UINT& _iCount) { m_iCount = _iCount; }
private:
    Item* m_pItem;
    UINT  m_iCount;
};

