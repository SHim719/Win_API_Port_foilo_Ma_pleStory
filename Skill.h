#pragma once

#include "Enrollable.h"
#include "Entity.h"
#include "joObject.h"
#include "Player.h"

enum class Skill_Enums
{
	PhantomBlow,
	KarmaFury,
	BladeStorm,
	Asura,
	SuddenRaid,
	End,
};


struct SkillInfo
{
	UINT iPoint = 0;
	UINT iMaxPoint = 5;
	float fCooltime = 0.f;
};

class JoTexture;

class Skill : public Entity, public Enrollable
{
public:
	Skill();
	~Skill();

	virtual void Initialize();

	void AddPoint()
	{
		m_tInfo.iPoint += 1;
		if (m_pIconTex == m_pSkillIconDisabledTex)
			m_pIconTex = m_pSkillIconTex;
	}
	const UINT& GetSkillPoint() { return m_tInfo.iPoint; }
	
	bool IsMaxPoint() { return m_tInfo.iPoint == m_tInfo.iMaxPoint; }

	static void SetOwner(Player* _pPlayer) { m_pOwner = _pPlayer; }
protected:
	static Player* m_pOwner;
	SkillInfo m_tInfo;
	float m_fCooltime;

	JoTexture* m_pSkillIconTex;
	JoTexture* m_pSkillIconDisabledTex;
};

