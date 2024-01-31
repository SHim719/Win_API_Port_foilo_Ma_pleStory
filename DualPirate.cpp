#include "DualPirate.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "joObject.h"
#include "AttackCollider.h"
#include "Player.h"
#include "DamageNum.h"

float DualPirate::m_fRespawnTime = 0.f;
HDC DualPirate::m_Pixel = nullptr;

DualPirate::DualPirate()
	: m_eState(State::End)
	, m_bRight(true)
	, m_fStateTime(0.f)
	, m_fNowTime(0.f)
	, m_fSpeed(0.f)
{
}

DualPirate::~DualPirate()
{
}

void DualPirate::Initialize()
{
	m_iMaxHp = 900000;
	m_iHp = m_iMaxHp;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(170.f, 82.f));

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pRigidbody = new Rigidbody;
	m_pRigidbody->SetOwner(this);
	m_pRigidbody->SetUseGravity(false);

	m_vAttackCollOffset = Vec2(104.f, 0.f);

	m_pAttackColl = Instantiate<AttackCollider>(eLayerType::LT_MONSTER_EFFECT);
	m_pAttackColl->SetOwner(this);
	m_pAttackColl->SetCollisionSize(Vec2(100.f, 50.f));
	m_pAttackColl->SetCollisionOnOff(true);
	m_pAttackColl->SetCollisionOffset(-m_vAttackCollOffset);

	m_fSpeed = 100.f;

	JoTexture* pLeftTex = ResourceMgr::Find<JoTexture>(L"DualPirate_L");
	JoTexture* pRightTex = ResourceMgr::Find<JoTexture>(L"DualPirate_R");

	m_pAnimator->CreateAnimation(L"DualPirate_Move_L", pLeftTex, Vec2(0.f, 0.f), Vec2(173.f, 190.f), Vec2(0.f, -5.0f), 6, 0.2f);
	m_pAnimator->CreateAnimation(L"DualPirate_Move_R", pRightTex, Vec2(0.f, 0.f), Vec2(173.f, 190.f), Vec2(0.f, -5.0f), 6, 0.2f);
	m_pAnimator->CreateAnimation(L"DualPirate_Idle_L", pLeftTex, Vec2(1038.f, 0.f), Vec2(176.f, 179.f), Vec2::Zero, 6, 0.2f);
	m_pAnimator->CreateAnimation(L"DualPirate_Idle_R", pRightTex, Vec2(1038.f, 0.f), Vec2(176.f, 179.f), Vec2::Zero, 6, 0.2f);
	m_pAnimator->CreateAnimation(L"DualPirate_Dead_L", pLeftTex, Vec2(2094.f, 0.f), Vec2(171.f, 174.f), Vec2::Zero, 14, 0.1f);
	m_pAnimator->CreateAnimation(L"DualPirate_Dead_R", pRightTex, Vec2(2094.f, 0.f), Vec2(171.f, 174.f), Vec2::Zero, 14, 0.1f);
	m_pAnimator->CreateAnimation(L"DualPirate_Attack_L", pLeftTex, Vec2(0.f, 190.f), Vec2(229.f, 191.f), Vec2(-27.f, -7.f), 18, 0.15f);
	m_pAnimator->CreateAnimation(L"DualPirate_Attack_R", pRightTex, Vec2(0.f, 190.f), Vec2(229.f, 191.f), Vec2(27.f, -7.f), 18, 0.15f);
	

	Events* pEvent_Attack_L = m_pAnimator->GetEvents(L"DualPirate_Attack_L");
	pEvent_Attack_L->frameEvents[2] = bind(&AttackCollider::SetHitOn, m_pAttackColl);
	pEvent_Attack_L->frameEvents[4] = bind(&AttackCollider::SetHitOff, m_pAttackColl);
	pEvent_Attack_L->EndEvent = bind(&DualPirate::SetState_Move, this);
	Events* pEvent_Attack_R = m_pAnimator->GetEvents(L"DualPirate_Attack_R");
	pEvent_Attack_R->frameEvents[2] = bind(&AttackCollider::SetHitOn, m_pAttackColl);
	pEvent_Attack_R->frameEvents[4] = bind(&AttackCollider::SetHitOff, m_pAttackColl);
	pEvent_Attack_R->EndEvent = bind(&DualPirate::SetState_Move, this);

	Events* pEvent_Dead_L = m_pAnimator->GetEvents(L"DualPirate_Dead_L");
	pEvent_Dead_L->EndEvent = bind(&DualPirate::SetState_Respawn, this);
	Events* pEvent_Dead_R = m_pAnimator->GetEvents(L"DualPirate_Dead_R");
	pEvent_Dead_R->EndEvent = bind(&DualPirate::SetState_Respawn, this);

	m_fStateTime = 2.f;
	SetState_Idle();
}

void DualPirate::Update()
{
	switch (m_eState)
	{
	case DualPirate::State::Respawn:
		Respawn();
		break;
	case DualPirate::State::Idle:
		Idle();
		break;
	case DualPirate::State::Move:
		Move();
		break;
	case DualPirate::State::Attack:
		Attack();
		break;
	case DualPirate::State::Dead:
		Dead();
		break;
	}

	m_pRigidbody->Update();
	m_pAnimator->Update();
}

void DualPirate::Render()
{
	m_pAnimator->Render();
	//m_pCollider->Render();
}

void DualPirate::OnCollisionStay(Collider* _pOther)
{
	Player* _pPlayer = dynamic_cast<Player*>(_pOther->GetOwner());
	if (_pPlayer)
	{
		HitInfo _info = { 300, 1 };
		_pPlayer->Hit(_info);
	}
}

void DualPirate::Hit(const HitInfo& _hitInfo)
{
	AddHp(-_hitInfo.iDamage);
	DamageNum* pDNum = Instantiate<DamageNum>(eLayerType::LT_UI);
	pDNum->Init_Number(std::to_string(_hitInfo.iDamage));
	pDNum->SetCritical(_hitInfo.bCritical);

	Vec2 vRenderPos = GetPos();
	JoTexture* pDamageTex = pDNum->GetDamageTex();
	vRenderPos.y -= float(pDamageTex->GetHeight()) * 0.5f * _hitInfo.iHitCount;

	pDNum->SetPos(vRenderPos);
}

void DualPirate::Idle()
{
	m_fNowTime += TimeMgr::DeltaTime();

	if (m_fNowTime >= m_fStateTime)
	{
		SetState_Move();
	}
}

void DualPirate::Move()
{
	m_fNowTime += TimeMgr::DeltaTime();

	if (m_fNowTime >= m_fStateTime)
	{
		SetState_Idle();
	}

	Check_RightLeft();
}

void DualPirate::Attack()
{
}

void DualPirate::Dead()
{
}

void DualPirate::Respawn()
{
	static float m_fNowTime = 0.f;

	m_fNowTime += TimeMgr::DeltaTime();
	if (m_fNowTime >= m_fRespawnTime)
	{
		m_fNowTime = 0.f;
		m_bRight = false;
		SetPos(m_vRespawnPos);

		m_pAttackColl->SetCollisionOnOff(true);
		m_pAttackColl->SetCollisionOffset(-m_vAttackCollOffset);
		m_pCollider->SetCollisionActive();
		m_iHp = m_iMaxHp;
		SetState_Idle();
	}
}

void DualPirate::SetState_Idle()
{
	m_pRigidbody->SetVelocity(Vec2::Zero);
	m_fStateTime = float(rand() % 2 + 1);
	m_fNowTime = 0.f;

	if (m_bRight)
		m_pAnimator->PlayAnimation(L"DualPirate_Idle_R", true);
	else
		m_pAnimator->PlayAnimation(L"DualPirate_Idle_L", true);

	m_eState = State::Idle;
}

void DualPirate::SetState_Move()
{
	m_fStateTime = float(rand() % 4 + 1);
	m_fNowTime = 0.f;

	if (m_bRight)
	{
		m_pAnimator->PlayAnimation(L"DualPirate_Move_R", true);
		m_pRigidbody->SetVelocity(Vec2(m_fSpeed, 0.f));
	}
	else
	{
		m_pAnimator->PlayAnimation(L"DualPirate_Move_L", true);
		m_pRigidbody->SetVelocity(Vec2(-m_fSpeed, 0.f));
	}

	m_eState = State::Move;
}

void DualPirate::SetState_Dead()
{
	if (m_eState == State::Dead)
		return;
	Enemy::SetState_Dead();
	m_pRigidbody->SetVelocity(Vec2::Zero);
	m_pAttackColl->SetCollisionOnOff(false);
	m_pCollider->SetCollisionInactive();

	SoundMgr::Play(L"Pirate_Die");

	if (m_bRight)
		m_pAnimator->PlayAnimation(L"DualPirate_Dead_R", false);
	else
		m_pAnimator->PlayAnimation(L"DualPirate_Dead_L", false);

	m_eState = State::Dead;
}

void DualPirate::SetState_Attack()
{
	if (m_eState == State::Attack)
		return;

	SoundMgr::Play(L"Pirate_Attack");
	m_pRigidbody->SetVelocity(Vec2::Zero);

	if (m_bRight)
		m_pAnimator->PlayAnimation(L"DualPirate_Attack_R", false);
	else
		m_pAnimator->PlayAnimation(L"DualPirate_Attack_L", false);

	m_eState = State::Attack;
}

void DualPirate::SetState_Respawn()
{
	if (m_eState == State::Respawn)
		return;
	m_pAnimator->SetActiveAnim(nullptr);
	m_eState = State::Respawn;
}

void DualPirate::Check_RightLeft()
{
	int iOffset = m_bRight ? 1 : -1;
	Vec2 vPos = GetPos();
	COLORREF color = GetPixel(m_Pixel, (int)vPos.x + iOffset, (int)vPos.y);

	if (color == RGB(255, 125, 0))
	{
		if (m_bRight)
		{
			m_bRight = false;
			m_pAnimator->PlayAnimation(L"DualPirate_Move_L", true);
			m_pRigidbody->SetVelocity(Vec2(-m_fSpeed, 0.f));
			m_pAttackColl->SetCollisionOffset(-m_vAttackCollOffset);
		}
		else
		{
			m_bRight = true;
			m_pAnimator->PlayAnimation(L"DualPirate_Move_R", true);
			m_pRigidbody->SetVelocity(Vec2(m_fSpeed, 0.f));
			m_pAttackColl->SetCollisionOffset(m_vAttackCollOffset);
		}
		m_fStateTime += 1.f;
	}
}


