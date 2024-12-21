#pragma once

#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "Animator.h"
#include "Rigidbody.h"

class Collider;
class Animator;
class Rigidbody;

class GameObject : public Entity
{
public:
	enum class eLifeCycle
	{
		Active,
		inActive,
		Dead,
		End,
	};

	GameObject();
	virtual ~GameObject();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

	void SetActive(const bool& active)
	{
		if (active)
			m_eLifeCycle = eLifeCycle::Active;
		else
			m_eLifeCycle = eLifeCycle::inActive;
	}
	void SetDeath() { m_eLifeCycle = eLifeCycle::Dead; }

	bool IsDeath() const { return m_eLifeCycle == eLifeCycle::Dead; }
	bool IsActive() const { return m_eLifeCycle == eLifeCycle::Active; }
	bool IsDontDestroy() const { return m_bDonDestroy; }

	void SetPos(const Vec2& _vPos) { m_tTransform.vPos = _vPos; }
	const Vec2& GetPos() const { return m_tTransform.vPos; }

	Collider* GetCollider() const { return m_pCollider; }
	Animator* GetAnimator() const { return m_pAnimator; }
	Rigidbody* GetRigidbody() const { return m_pRigidbody; }

	virtual void OnCollisionEnter(Collider* other) {};
	virtual void OnCollisionStay(Collider* other) {};
	virtual void OnCollisionExit(Collider* other) {};

protected:
	eLifeCycle	m_eLifeCycle;
	Transform	m_tTransform;
	Collider*	m_pCollider;
	Animator*	m_pAnimator;
	Rigidbody*	m_pRigidbody;

	bool		m_bDonDestroy;
};

