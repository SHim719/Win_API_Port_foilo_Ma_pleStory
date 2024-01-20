#include "Hat.h"

Hat::Hat()
	: Equipable(EquipType::ET_HEAD)
{
	SetName(L"Hat");
}

Hat::~Hat()
{
}

void Hat::Initialize()
{
	m_pItemTex = ResourceMgr::Load<JoTexture>(L"Hat", L"Resource/Item/Hat.png");

	m_tEquipInfo.iStr = 50;
	m_tEquipInfo.iDex = 50;
	m_tEquipInfo.iInt = 10;
	m_tEquipInfo.iLuk = 100;
	m_tEquipInfo.iHp = 5000;
	m_tEquipInfo.iMp = 1000;
}
