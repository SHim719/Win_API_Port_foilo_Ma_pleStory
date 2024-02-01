#include "Skill.h"

Player* Skill::m_pOwner = nullptr;

Skill::Skill()
	: m_pSkillIconTex(nullptr)
	, m_pSkillIconDisabledTex(nullptr)
	, m_fCooltime(0.f)
	, m_fNowTime(0.f)
	, m_bUsingSkill(false)
	, m_iUseMp(0)
{
}

Skill::~Skill()
{
}

void Skill::Initialize()
{
}
