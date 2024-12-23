#pragma once
#include "Skill.h"

class BladeStorm :
    public Skill
{
public:
	BladeStorm();
	~BladeStorm();

	void Initialize()						override;
	void Render(const Vec2& vLeftTop)		override;
	void Key_Check(const eKeyCode& _key)	override;

private:
	void Execution();
	void Execution_Loop();
	void Execution_End();

	bool m_bPrevRight;

	float m_fMaxDuration;
	float m_fNowDuration;

	float m_fMpCheckGap;
};
