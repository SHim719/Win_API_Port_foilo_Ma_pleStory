#pragma once
#include "Skill.h"

class BladeTornado :
    public Skill
{
public:
	BladeTornado();
	~BladeTornado();

	void Initialize()						override;
	void Render(const Vec2& vLeftTop)		override;
	void Key_Check(const eKeyCode& _key)	override;

private:
	void Execution();

};

