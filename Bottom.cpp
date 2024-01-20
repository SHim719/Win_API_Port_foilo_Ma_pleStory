#include "Bottom.h"


Bottom::Bottom()
	: Equipable(EquipType::ET_BOTTOM)
{
	SetName(L"Bottom");
}

Bottom::~Bottom()
{
}

void Bottom::Initialize()
{
	m_pItemTex = ResourceMgr::Load<JoTexture>(L"Bottom", L"Resource/Item/Bottom.png");

	m_tEquipInfo.iStr = 50;
	m_tEquipInfo.iDex = 50;
	m_tEquipInfo.iInt = 10;
	m_tEquipInfo.iLuk = 100;
	m_tEquipInfo.iHp = 5000;
	m_tEquipInfo.iMp = 1000;
}