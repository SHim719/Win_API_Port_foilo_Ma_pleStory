#include "PlayerStats.h"

PlayerStats::PlayerStats()
	: m_iHp(3000)
	, m_iMp(3000)
	, m_iStr(4)
	, m_iDex(4)
	, m_iInt(4)
	, m_iLuk(50)
	, m_iAttack(300)
	, m_iExtra_Str(0)
	, m_iExtra_Dex(0)
	, m_iExtra_Int(0)
	, m_iExtra_Luk(0)
	, m_iRemaining_Point(0)
{
	m_iRemaining_Point = 100;
}

PlayerStats::~PlayerStats()
{
}

void PlayerStats::Add_EquipAbility(const EquipInfo& _info)
{
	m_iExtra_Str += _info.iStr;
	m_iExtra_Dex += _info.iDex;
	m_iExtra_Int += _info.iInt;
	m_iExtra_Luk += _info.iLuk;

	m_iAttack += _info.iAttack;
	m_iHp += _info.iHp;
	m_iMp += _info.iMp;
}

void PlayerStats::Sub_EquipAbility(const EquipInfo& _info)
{
	m_iExtra_Str -= _info.iStr;
	m_iExtra_Dex -= _info.iDex;
	m_iExtra_Int -= _info.iInt;
	m_iExtra_Luk -= _info.iLuk;

	m_iAttack -= _info.iAttack;
	m_iHp -= _info.iHp;
	m_iMp -= _info.iMp;
}
