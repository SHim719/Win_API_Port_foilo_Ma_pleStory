#include "Top.h"

Top::Top()
	: Equipable(EquipType::ET_TOP)
{
	SetName(L"Top");
}

Top::~Top()
{
}

void Top::Initialize()
{
	m_pItemTex = ResourceMgr::Load<JoTexture>(L"Top", L"Resource/Item/Top.png");

	m_tEquipInfo.iStr = 50;
	m_tEquipInfo.iDex = 50;
	m_tEquipInfo.iInt = 10;
	m_tEquipInfo.iLuk = 100;
	m_tEquipInfo.iHp = 5000;
	m_tEquipInfo.iMp = 1000;
}