#pragma once

#include "Entity.h"

class GameObject;

class Rigidbody : public Entity
{
public:
	Rigidbody();
	~Rigidbody();

	void Update();

	void SetMass(const float& mass) { m_fMass = mass; }

	void AddForce(const Vec2& force) { m_vForce = force; }

	void SetVelocity(const Vec2& velocity) { m_vVelocity = velocity; }
	void SetVelocityX(const float& f) { m_vVelocity.x = f; }
	void SetVelocityY(const float& f) { m_vVelocity.y = f; }
	void AddVelocity(const Vec2& velocity) { m_vVelocity += velocity; }
	const Vec2& GetVelocity() const { return m_vVelocity; }

	void SetLimitedVelocity(const Vec2& velocity) { m_vLimitedVelocity = velocity; }
	const Vec2& GetLimitedVelocity() const { return m_vLimitedVelocity; }

	void SetGravity(const Vec2& gravity) { m_vGravity = gravity; }

	void SetGround(const bool& isGround) { m_bIsGround = isGround; }
	const bool& IsGround() const { return m_bIsGround; }

	void SetUseGravity(const bool& _bUse) { m_bUseGravity = _bUse; }

	void SetOwner(GameObject* _pOwner) { m_pOwner = _pOwner; }
	GameObject* GetOwner() const { return m_pOwner; }

	void SetActive(const bool& _b) { m_bActive = _b; }
private:
	bool m_bActive;
	bool m_bIsGround;
	bool m_bUseGravity;

	float m_fMass;
	float m_fFriction;

	Vec2 m_vGravity;
	Vec2 m_vForce;
	Vec2 m_vAccel;
	Vec2 m_vVelocity;
	Vec2 m_vLimitedVelocity;

	GameObject* m_pOwner;
};

