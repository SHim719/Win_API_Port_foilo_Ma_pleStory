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


class Item : public Entity
{
public:
	Item(const ItemType& type);
	~Item();

	virtual void Initialize() {};

	void SetItemType(const ItemType& type) { m_eItemType = type; }
	const ItemType& GetItemType() const { return m_eItemType; }

	void SetItemTex(JoTexture* tex) { m_pItemTex = tex; }
	JoTexture* GetItemTex() const { return m_pItemTex; }

	const UINT& GetMaxCount() const { return m_iMaxCount; }

	const UINT& GetSellPrice() const { return m_iSellPrice; }
protected:
    JoTexture*	 m_pItemTex;
	ItemType	 m_eItemType;
	UINT		 m_iMaxCount;
	UINT	     m_iSellPrice;
};

