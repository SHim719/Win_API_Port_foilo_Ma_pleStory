#pragma once
#include "Skill.h"


class KarmaFury :
    public Skill
{
public:
	KarmaFury();
	~KarmaFury();

	void Initialize()						override;
	void Render(const Vec2& vLeftTop)		override;
	void Key_Check(const eKeyCode& _key)	override;

private:
	void Execution();

};

