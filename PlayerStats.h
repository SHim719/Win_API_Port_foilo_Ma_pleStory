#pragma once

#include "Equipable.h"


class Player;
class SkillStats;

class PlayerStats
{
public:
	PlayerStats();
	~PlayerStats();

	void Add_EquipAbility(const EquipInfo& _info);
	void Sub_EquipAbility(const EquipInfo& _info);

	void Add_StatPoint(const int& _iPoint) { m_iRemaining_Point += _iPoint; }
	const int& Get_StatPoint() const { return m_iRemaining_Point; }

	void Add_Str(const int& _iPoint) { m_iStr += _iPoint; }
	void Add_Dex(const int& _iPoint) { m_iDex += _iPoint; }
	void Add_Int(const int& _iPoint) { m_iInt += _iPoint; }
	void Add_Luk(const int& _iPoint) { m_iLuk += _iPoint; }

	void Add_Exp(const int& _iExp);

	const int& Get_Str() const { return m_iStr; }
	const int& Get_Dex() const { return m_iDex; }
	const int& Get_Int() const { return m_iInt; }
	const int& Get_Luk() const { return m_iLuk; }
	const int& Get_Extra_Str() const { return m_iExtra_Str; }
	const int& Get_Extra_Dex() const { return m_iExtra_Dex; }
	const int& Get_Extra_Int() const { return m_iExtra_Int; }
	const int& Get_Extra_Luk() const { return m_iExtra_Luk; }

	void Set_FullHP() { m_iHp = m_iMaxHp; }
	void Set_FullMP() { m_iMp = m_iMaxMp; }
	void Add_HP(const int& _iHp);
	void Add_MP(const int& _iMp);

	const int& Get_MaxHp() const { return m_iMaxHp; }
	const int& Get_MaxMp() const { return m_iMaxMp; }
	const int& Get_Hp() const { return m_iHp; }
	const int& Get_Mp() const { return m_iMp; }

	const int& Get_Exp() const { return m_iExp; }
	const int& Get_MaxExp() const { return m_iMaxExp; }

	void Set_SkillStats(SkillStats* const _pStats) { m_pSkillStats = _pStats; }
	void Set_Player(Player* const _pPlayer) { m_pPlayer = _pPlayer; }
private:
	void LevelUp();
private:
	int m_iHp;
	int m_iMp;
	int m_iMaxHp;
	int m_iMaxMp;
	int m_iStr;
	int m_iDex;
	int m_iInt;
	int m_iLuk;
		
	int m_iAttack;
		
	int m_iExtra_Str;
	int m_iExtra_Dex;
	int m_iExtra_Int;
	int m_iExtra_Luk;

	int m_iRemaining_Point;

	int m_iLevel;
	int m_iMaxExp;
	int m_iExp;

	SkillStats* m_pSkillStats;
	Player* m_pPlayer;
};

