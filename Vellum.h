#pragma once

#include "Enemy.h"

class VellumAttackCollider;

enum class Vellum_State
{
	Move,
	Appear,
	LowNeck,
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	Breath,
	Dig,
	End
};

class Vellum : public Enemy
{
public:
	Vellum();
	~Vellum();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	void Hit(const HitInfo& _hitInfo);

	void SetState_Move();
	void SetState_Move_NoAnim();
	void SetState_Appear();
	void SetState_LowNeck();
	void SetState_Attack1();
	void SetState_Attack2();
	void SetState_Attack3();
	void SetState_Attack4();
	void SetState_Breath();
	void SetState_Dig();

private:
	void debug_key();

	void Init_Anim();
	void Init_AnimKey();
	void Init_AnimBind();

	void Appear_Attack();
	void LowNeck_Attack();
	void Attack2_Attack();
	void Attack3_Attack();
	void Attack4_Attack();
	void AttackCollisionOff();
	
	void End_State();
	void EndState_Move();
	void EndState_Appear();
	void EndState_Attack2();
	void EndState_Attack3();
	void EndState_Attack4();
	void EndState_Dig();
	
	void Move();
	void Breath();
private:
	Vellum_State m_eVellumState;

	float m_fSpeed = 0.f;

	bool m_bTimerOn = false;
	bool m_bRight = false;
	bool m_bHiding = false;

	float m_fMoveTime = 0.f;

	int m_iMaxShotCount = 0;
	int m_iShotCount = 0;
	int m_iTailCount = 0;

	float m_fBreath_LeftX = 175.f;
	float m_fBreath_RightX = 2880.f;

	VellumAttackCollider* m_pAttackCollider = nullptr;
};

