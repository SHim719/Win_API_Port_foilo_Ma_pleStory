#pragma once
#include "CommonInclude.h"



class Skill;

class SkillStats
{
public:
	SkillStats();
	~SkillStats();

	vector<Skill*>& Get_vecSkills()  { return m_vecSkills; }

	const int& GetRemainingPoint() const { return m_iRemainingPoint; }
	void AddPoint(int _iNum) { m_iRemainingPoint += _iNum; }
private:
	vector<Skill*> m_vecSkills;
	int m_iRemainingPoint;
};

