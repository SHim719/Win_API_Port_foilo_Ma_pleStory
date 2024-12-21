#pragma once
#include "Skill.h"
class SuddenRaid :
    public Skill
{
public:
	void Initialize()						override;
	void Render(const Vec2& vLeftTop)		override;
	void Key_Check(const eKeyCode& _key)	override;

private:
	void Execution();
};

