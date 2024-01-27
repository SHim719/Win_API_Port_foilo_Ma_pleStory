#include "Skill.h"

Player* Skill::m_pOwner = nullptr;

Skill::Skill()
	: m_pSkillIconTex(nullptr)
	, m_pSkillIconDisabledTex(nullptr)
	, m_fCooltime(0.f)
{
}

Skill::~Skill()
{
}

void Skill::Initialize()
{
}
