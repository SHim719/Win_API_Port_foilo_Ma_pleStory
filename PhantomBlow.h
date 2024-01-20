#pragma once

#include "Skill.h"

class PhantomBlow : public Skill
{
public:
	PhantomBlow();
	~PhantomBlow();

	void Initialize()						override;
	void Render(const Vec2& vLeftTop)		override;
	void Key_Check(const eKeyCode& _key)	override;

private:
	void Execution();
};

