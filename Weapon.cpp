#include "Weapon.h"

Weapon::Weapon()
	: Equipable(EquipType::ET_WEAPON)
{
	SetName(L"리버스 페스카즈");
}

Weapon::~Weapon()
{
}

void Weapon::Initialize()
{
	m_pItemTex = ResourceMgr::Load<JoTexture>(L"Weapon", L"Resources/Item/Weapon.png");

	m_tEquipInfo.iAttack = 5000;
}



