#pragma once
#include "Item.h"


enum class EquipType
{
	ET_HEAD,
	ET_TOP,
	ET_BOTTOM,
	ET_SHOES,
	ET_WEAPON,
	ET_END,
};

struct EquipInfo
{
	int iStr	  = 0;
	int	iDex 	  = 0;
	int	iInt	  = 0;
	int	iLuk	  = 0;
	int	iHp		  = 0;
	int	iMp 	  = 0;
	int	iAttack	  = 0;
};

class Equipable :
    public Item
{
public:
	Equipable(const EquipType& type);
	~Equipable();

	void Initialize() override {};

	void SetEquipType(const EquipType& type) { m_eEquipType = type; }
	const EquipType& GetEquipType() const { return m_eEquipType; }

	const EquipInfo& GetEquipInfo() const { return m_tEquipInfo; }

protected:
	EquipType m_eEquipType;
	EquipInfo m_tEquipInfo;
};

