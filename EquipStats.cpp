#include "EquipStats.h"
#include "PlayerStats.h"

EquipStats::EquipStats()
	: m_pArrEquipped{}
	, m_pPlayerStats(nullptr)
{
}

EquipStats::~EquipStats()
{
}

void EquipStats::Equip(Equipable* _pEquip)
{
	if (_pEquip == nullptr) 
		return;

	const EquipType& eType = _pEquip->GetEquipType();

	m_pArrEquipped[(UINT)eType] = _pEquip;

	// 능력치 올려주는 로직 처리
	m_pPlayerStats->Add_EquipAbility(_pEquip->GetEquipInfo());
}

void EquipStats::UnEquip(const EquipType& type)
{
	Equipable* pEquip = m_pArrEquipped[(UINT)type];
	if (pEquip == nullptr)
		return;

	m_pPlayerStats->Sub_EquipAbility(pEquip->GetEquipInfo());

	m_pArrEquipped[(UINT)type] = nullptr;
}

