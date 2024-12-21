#pragma once
#include "Eagle.h"


class BaldEagle :
    public Eagle
{
public:
	void Initialize()	override;

	void Hit(const HitInfo& _hitInfo) override;

};

