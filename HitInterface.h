#pragma once

#include "CommonInclude.h"
#include "DamageNum.h"



struct HitInfo
{
	int iDamage = 0;
	int iHitCount = 0;
	bool bCritical = false;
};



class HitInterface
{
public:
	virtual void Hit(const HitInfo& _hitInfo) = 0;
};



struct AttackInfo
{
	HitInterface* pHitObj = nullptr;
	vector<Vec2> vecEffectPos = {};
	float fNowTime;
	int iHitCount = 0;
};


