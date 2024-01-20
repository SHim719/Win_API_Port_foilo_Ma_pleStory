#include "Shoes.h"


Shoes::Shoes()
	: Equipable(EquipType::ET_SHOES)
{
	SetName(L"Shoes");
}

Shoes::~Shoes()
{
}

void Shoes::Initialize()
{
	m_pItemTex = ResourceMgr::Load<JoTexture>(L"Shoes", L"Resource/Item/Shoes.png");

	m_tEquipInfo.iStr = 50;
	m_tEquipInfo.iDex = 50;
	m_tEquipInfo.iInt = 10;
	m_tEquipInfo.iLuk = 100;
	m_tEquipInfo.iHp = 1000;
	m_tEquipInfo.iMp = 1000;
}