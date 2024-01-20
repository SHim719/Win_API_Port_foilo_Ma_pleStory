#pragma once
#include "GameObject.h"
#include "ResourceMgr.h"

enum class ItemType
{
	IT_EQUIPABLE,
	IT_CONSUMABLE,
	IT_ETC,
	IT_SET_UP,
	IT_CASH,
	IT_END,
};


class Item :
    public GameObject
{
public:
    Item();
    ~Item();

	void SetItemType(const ItemType& type) { m_eItemType = type; }
	const ItemType& GetItemType() const { return m_eItemType; }

protected:
    JoTexture* m_pItemTex;
	ItemType  m_eItemType;
};

