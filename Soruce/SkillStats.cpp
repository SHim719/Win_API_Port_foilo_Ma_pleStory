#include "SkillStats.h"
#include "Skill.h"
#include "PhantomBlow.h"
#include "KarmaFury.h"
#include "BladeTornado.h"
#include "BladeStorm.h"
#include "Asura.h"
#include "SuddenRaid.h"

SkillStats::SkillStats()
	: m_iRemainingPoint(6)
{
	m_vecSkills.reserve((UINT)Skill_Enums::End);

	Skill* pPhantomBlow = new PhantomBlow;
	pPhantomBlow->Initialize();
	m_vecSkills.push_back(pPhantomBlow);

	Skill* pKarmaFury = new KarmaFury;
	pKarmaFury->Initialize();
	m_vecSkills.push_back(pKarmaFury);

	Skill* pBladeTornado = new BladeTornado;
	pBladeTornado->Initialize();
	m_vecSkills.push_back(pBladeTornado);

	Skill* pBladeStorm = new BladeStorm;
	pBladeStorm->Initialize();
	m_vecSkills.push_back(pBladeStorm);

	Skill* pAsura = new Asura;
	pAsura->Initialize();
	m_vecSkills.push_back(pAsura);

	Skill* pSuddenRaid = new SuddenRaid;
	pSuddenRaid->Initialize();
	m_vecSkills.push_back(pSuddenRaid);
}

SkillStats::~SkillStats()
{
	for (Skill* skill : m_vecSkills)
		Safe_Delete<Skill*>(skill);

	m_vecSkills.clear();
	m_vecSkills.shrink_to_fit();
}
