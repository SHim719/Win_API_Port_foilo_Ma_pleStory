#include "SkillStats.h"
#include "Skill.h"
#include "PhantomBlow.h"

SkillStats::SkillStats()
	: m_iRemainingPoint(5)
{
	m_vecSkills.reserve((UINT)Skill_Enums::End);

	Skill* pPhantomBlow = new PhantomBlow;
	pPhantomBlow->Initialize();
	m_vecSkills.push_back(pPhantomBlow);
}

SkillStats::~SkillStats()
{
	for (Skill* skill : m_vecSkills)
		Safe_Delete<Skill*>(skill);

	m_vecSkills.clear();
	m_vecSkills.shrink_to_fit();
}
