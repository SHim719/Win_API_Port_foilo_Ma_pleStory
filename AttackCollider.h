#pragma once
#include "Enemy.h"

class AttackCollider :
    public GameObject
{
public:
	void Initialize()	override;
	void Update()		override;
	void Render()		override;

	void OnCollisionEnter(Collider* _pother) override;
	void OnCollisionStay(Collider* _pOther) override;

	void SetCollisionSize(const Vec2& _vSize);
	void SetCollisionOffset(const Vec2& _vOffset);
	void SetCollisionOnOff(const bool& _b);

	void SetOwner(Enemy* const _pOwner) { m_pOwner = _pOwner; }
	void SetHitOn() { m_bCanHit = true; }
	void SetHitOff() { m_bCanHit = false; }
private:
	int iDamage = 0;
	Enemy* m_pOwner;

	bool m_bCanHit;
};

