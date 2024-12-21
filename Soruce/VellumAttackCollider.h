#pragma once
#include "GameObject.h"



class VellumAttackCollider :
    public GameObject
{
public:
	void Initialize()	override;
	void Render()		override;

	void OnCollisionEnter(Collider* other) override;
	
	void SetCollisionSize(const Vec2& _vSize);
	void SetCollisionOffset(const Vec2& _vOffset);
	void SetCollisionOnOff(const bool& _b);

	void SetDamage(const int& _iDamage) { iDamage = _iDamage; }
private:
	int iDamage = 0;
};

