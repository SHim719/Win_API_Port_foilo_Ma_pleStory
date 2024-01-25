#include "Vellum.h"
#include "ResourceMgr.h"
#include "joObject.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "VellumAttackCollider.h"
#include "DeepBreath.h"
#include "Tail.h"


Vellum::Vellum()
	: m_eVellumState(Vellum_State::Attack1)
{
}

Vellum::~Vellum()
{
}

void Vellum::Initialize()
{
	m_iMaxHp = 5000000;
	m_iHp = 2;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(200.f, 400.f));
	m_pCollider->SetOffset(Vec2(30.f, 100.f));

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_fSpeed = 200.f;

	m_pAttackCollider = Instantiate<VellumAttackCollider>(eLayerType::LT_MONSTER);

	m_vecBreath.reserve(6);
	for (int i = 0; i < 6; ++i)
	{
		DeepBreath* pdb = Instantiate<DeepBreath>(eLayerType::LT_MONSTER);
		m_vecBreath.push_back(pdb);
	}

	Init_Anim();
	Init_AnimKey();
	Init_AnimBind();
}

void Vellum::Update()
{
	debug_key();

	Attack_Tail();

	switch (m_eVellumState)
	{
	case Vellum_State::Move:
		Move();
		break;
	case Vellum_State::Attack1:
		break;
	case Vellum_State::Attack2:
		break;
	case Vellum_State::Attack3:
		break;
	case Vellum_State::Attack4:
		break;
	case Vellum_State::Breath:
		Breath();
		break;
	default:
		break;
	}

	m_pAnimator->Update();
}

void Vellum::LateUpdate()
{
}

void Vellum::Render()
{
	m_pAnimator->Render();
	//m_pCollider->Render();
}

void Vellum::Hit(const HitInfo& _hitInfo)
{
	DamageNum* pDNum = Instantiate<DamageNum>(eLayerType::LT_UI);
	pDNum->Init_Number(std::to_string(_hitInfo.iDamage));
	pDNum->SetCritical(_hitInfo.bCritical);

	Vec2 vDamagePos = GetPos();
	JoTexture* pDamageTex = pDNum->GetDamageTex();
	vDamagePos.x -= 250.f;
	vDamagePos.y -= float(pDamageTex->GetHeight()) * 0.5f * _hitInfo.iHitCount;

	pDNum->SetPos(vDamagePos);
}

void Vellum::debug_key()
{
	if (KeyMgr::GetKeyDown(eKeyCode::W))
	{
		//SetState_Move();
		//SetState_Appear();
		//SetState_Attack1();
		//SetState_LowNeck();
		SetState_Breath();
	}
}

void Vellum::Play_Breath_Loop()
{
	SoundMgr::Play(L"Vellum_Attack10");

	if (m_bRight)
		m_pAnimator->PlayAnimation(L"Vellum_Breath_Loop_R");
	else
		m_pAnimator->PlayAnimation(L"Vellum_Breath_Loop_L");
	m_bTimerOn = true;

	for (size_t i = 0; i < 6; ++i)
	{
		m_vecBreath[i]->SetActive(true);
		Vec2 vPos = Vec2::Zero;
		if (m_bRight)
			vPos = m_vBreathLeftStartPos + Vec2(340.f * float(i), 0.f);
		else
			vPos = m_vBreathRightStartPos - Vec2(340.f * float(i), 0.f);
		m_vecBreath[i]->SetPos(vPos);
		m_vecBreath[i]->Play_BreathAnim(m_bRight);
	}
}

void Vellum::Init_Anim()
{
	JoTexture* m_pMoveTex = ResourceMgr::Find<JoTexture>(L"Vellum_Move");
	JoTexture* m_pAttack1Tex_L = ResourceMgr::Find<JoTexture>(L"Vellum_Attack1_L");
	JoTexture* m_pAttack1Tex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Attack1_R");
	JoTexture* m_pAttack2Tex_L = ResourceMgr::Find<JoTexture>(L"Vellum_Attack2_L");
	JoTexture* m_pAttack2Tex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Attack2_R");
	JoTexture* m_pAttack3Tex_L = ResourceMgr::Find<JoTexture>(L"Vellum_Attack3_L");
	JoTexture* m_pAttack3Tex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Attack3_R");
	JoTexture* m_pAttack4Tex_L = ResourceMgr::Find<JoTexture>(L"Vellum_Attack4_L");
	JoTexture* m_pAttack4Tex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Attack4_R");
	JoTexture* m_pBreathStartTex_L = ResourceMgr::Find<JoTexture>(L"Vellum_Breath_Start_L");
	JoTexture* m_pBreathStartTex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Breath_Start_R");
	JoTexture* m_pBreathLoopTex_L = ResourceMgr::Find<JoTexture>(L"Vellum_Breath_Loop_L");
	JoTexture* m_pBreathLoopTex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Breath_Loop_R");
	JoTexture* m_pBreathEnd_L = ResourceMgr::Find<JoTexture>(L"Vellum_Breath_Loop_End_L");
	JoTexture* m_pBreathEnd_R = ResourceMgr::Find<JoTexture>(L"Vellum_Breath_Loop_End_R");
	JoTexture* m_pDig_L = ResourceMgr::Find<JoTexture>(L"Vellum_Dig_L");
	JoTexture* m_pDig_R = ResourceMgr::Find<JoTexture>(L"Vellum_Dig_R");
	JoTexture* m_pLowNeck_L = ResourceMgr::Find<JoTexture>(L"Vellum_LowNeck_L");
	JoTexture* m_pLowNeck_R = ResourceMgr::Find<JoTexture>(L"Vellum_LowNeck_R");
	JoTexture* m_pAppear_L = ResourceMgr::Find<JoTexture>(L"Vellum_Appear_L");
	JoTexture* m_pAppear_R = ResourceMgr::Find<JoTexture>(L"Vellum_Appear_R");
	JoTexture* m_pDieTex_L = ResourceMgr::Find<JoTexture>(L"Vellum_Die_L");
	JoTexture* m_pDieTex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Die_R");

	m_pAnimator->CreateAnimation(L"Vellum_Move", m_pMoveTex, Vec2::Zero, Vec2(412.f, 206.f), Vec2(0.f, 280.f), 10, 0.12f);

	m_pAnimator->CreateAnimation(L"Vellum_Attack1_L", m_pAttack1Tex_L, Vec2::Zero, Vec2(996.f, 776.f), Vec2(-8.f, 10.f), 33, 7, 0.1f);
	m_pAnimator->CreateAnimation(L"Vellum_Attack1_R", m_pAttack1Tex_R, Vec2::Zero, Vec2(996.f, 776.f), Vec2(10.f, 10.f), 33, 7, 0.1f);

	m_pAnimator->CreateAnimation(L"Vellum_Attack2_L", m_pAttack2Tex_L, Vec2::Zero, Vec2(1498.f, 859.f), Vec2(-541.f, -67.f), 28, 5, 0.065f);
	m_pAnimator->CreateAnimation(L"Vellum_Attack2_R", m_pAttack2Tex_R, Vec2::Zero, Vec2(1498.f, 859.f), Vec2(540.f, -67.f), 28, 5, 0.065f);

	m_pAnimator->CreateAnimation(L"Vellum_Attack3_L", m_pAttack3Tex_L, Vec2::Zero, Vec2(1220.f, 868.f), Vec2(-400.f, -61.f), 27, 7, 0.065f);
	m_pAnimator->CreateAnimation(L"Vellum_Attack3_R", m_pAttack3Tex_R, Vec2::Zero, Vec2(1220.f, 868.f), Vec2(400.f, -61.f), 27, 7, 0.065f);

	m_pAnimator->CreateAnimation(L"Vellum_Attack4_L", m_pAttack4Tex_L, Vec2::Zero, Vec2(1696.f, 720.f), Vec2(-500.f, 39.f), 32, 4, 0.1f);
	m_pAnimator->CreateAnimation(L"Vellum_Attack4_R", m_pAttack4Tex_R, Vec2::Zero, Vec2(1696.f, 720.f), Vec2(500.f, 39.f), 32, 4, 0.1f);

	m_pAnimator->CreateAnimation(L"Vellum_Dig_L", m_pDig_L, Vec2::Zero, Vec2(714.f, 776.f), Vec2(-96.f, 11.f), 13, 7, 0.1f);
	m_pAnimator->CreateAnimation(L"Vellum_Dig_R", m_pDig_R, Vec2::Zero, Vec2(714.f, 776.f), Vec2(96.f, 11.f), 13, 7, 0.1f);

	m_pAnimator->CreateAnimation(L"Vellum_LowNeck_L", m_pLowNeck_L, Vec2::Zero, Vec2(996.f, 720.f), Vec2(-47.f, 39.f), 33, 7, 0.08f);
	m_pAnimator->CreateAnimation(L"Vellum_LowNeck_R", m_pLowNeck_R, Vec2::Zero, Vec2(996.f, 720.f), Vec2(47.f, 39.f), 33, 7, 0.08f);

	m_pAnimator->CreateAnimation(L"Vellum_Breath_Appear_L", m_pAppear_L, Vec2::Zero, Vec2(1564.f, 1108.f), Vec2(-288.f, -109.f), 21, 6, 0.1f);
	m_pAnimator->CreateAnimation(L"Vellum_Breath_Appear_R", m_pAppear_R, Vec2::Zero, Vec2(1564.f, 1108.f), Vec2(288.f, -109.f), 21, 6, 0.1f);

	m_pAnimator->CreateAnimation(L"Vellum_Appear_L", m_pAppear_L, Vec2::Zero, Vec2(1564.f, 1108.f), Vec2(-288.f, -109.f), 21, 6, 0.1f);
	m_pAnimator->CreateAnimation(L"Vellum_Appear_R", m_pAppear_R, Vec2::Zero, Vec2(1564.f, 1108.f), Vec2(288.f, -109.f), 21, 6, 0.1f);

	m_pAnimator->CreateAnimation(L"Vellum_Breath_Start_L", m_pBreathStartTex_L, Vec2::Zero, Vec2(1564.f, 1108.f), Vec2(-288.f, -109.f), 31, 5, 0.127f);
	m_pAnimator->CreateAnimation(L"Vellum_Breath_Start_R", m_pBreathStartTex_R, Vec2::Zero, Vec2(1564.f, 1108.f), Vec2(288.f, -109.f), 31, 5, 0.127f);

	m_pAnimator->CreateAnimation(L"Vellum_Breath_Loop_L", m_pBreathLoopTex_L, Vec2::Zero, Vec2(1312.f, 876.f), Vec2(-346.f, -39.f), 12, 6, 0.1f);
	m_pAnimator->CreateAnimation(L"Vellum_Breath_Loop_R", m_pBreathLoopTex_R, Vec2::Zero, Vec2(1312.f, 876.f), Vec2(346.f, -39.f), 12, 6, 0.1f);

	m_pAnimator->CreateAnimation(L"Vellum_Breath_Loop_End_L", m_pBreathEnd_L, Vec2::Zero, Vec2(1177.f, 758.f), Vec2(-413.f, -22.f), 7, 0.1f);
	m_pAnimator->CreateAnimation(L"Vellum_Breath_Loop_End_R", m_pBreathEnd_R, Vec2::Zero, Vec2(1177.f, 758.f), Vec2(413.f, -22.f), 7, 0.1f);

	m_pAnimator->CreateAnimation(L"Vellum_Die_L", m_pDieTex_L, Vec2::Zero, Vec2(1008.f, 793.f), Vec2(-14.f, 20.f), 61, 8, 0.1f);
	m_pAnimator->CreateAnimation(L"Vellum_Die_R", m_pDieTex_R, Vec2::Zero, Vec2(1008.f, 793.f), Vec2(14.f, 20.f), 61, 8, 0.1f);
}

void Vellum::Init_AnimKey()
{
	Animation* pAnim = m_pAnimator->FindAnimation(L"Vellum_Attack1_L");
	pAnim->Set_AnimDuration(21, 1.0f);
	pAnim->Set_AnimDuration(22, 0.15f);
	pAnim->Set_AnimDuration(23, 0.15f);

	pAnim = m_pAnimator->FindAnimation(L"Vellum_Attack1_R");
	pAnim->Set_AnimDuration(21, 1.0f);
	pAnim->Set_AnimDuration(22, 0.15f);
	pAnim->Set_AnimDuration(23, 0.15f);

	pAnim = m_pAnimator->FindAnimation(L"Vellum_Attack4_L");
	pAnim->Set_AnimDuration(13, 1.0f);

	pAnim = m_pAnimator->FindAnimation(L"Vellum_Attack4_R");
	pAnim->Set_AnimDuration(13, 1.0f);

	pAnim = m_pAnimator->FindAnimation(L"Vellum_Dig_L");
	pAnim->Set_AnimDuration(0, 0.7f);

	pAnim = m_pAnimator->FindAnimation(L"Vellum_Dig_R");
	pAnim->Set_AnimDuration(0, 0.7f);

	pAnim = m_pAnimator->FindAnimation(L"Vellum_LowNeck_L");
	pAnim->Set_AnimDuration(20, 0.65f);
	pAnim->Set_AnimDuration(9, 0.2f);

	pAnim = m_pAnimator->FindAnimation(L"Vellum_LowNeck_R");
	pAnim->Set_AnimDuration(20, 0.65f);
	pAnim->Set_AnimDuration(9, 0.2f);

	pAnim = m_pAnimator->FindAnimation(L"Vellum_Appear_L");
	pAnim->Set_AnimDuration(20, 0.5f);
	pAnim = m_pAnimator->FindAnimation(L"Vellum_Appear_R");
	pAnim->Set_AnimDuration(20, 0.5f);

}

void Vellum::Init_AnimBind()
{
	Events* pEvent_Breath_Appear_L = m_pAnimator->GetEvents(L"Vellum_Breath_Appear_L");
	Events* pEvent_Breath_Appear_R = m_pAnimator->GetEvents(L"Vellum_Breath_Appear_R");
	function<void()> playBreathStart = [&]() ->void 
		{
			if (GetPos().x > 2000.f)
				m_pAnimator->PlayAnimation(L"Vellum_Breath_Start_L", false);
			else
				m_pAnimator->PlayAnimation(L"Vellum_Breath_Start_R", false);
		};
	pEvent_Breath_Appear_L->EndEvent = playBreathStart;
	pEvent_Breath_Appear_R->EndEvent = playBreathStart;
	pEvent_Breath_Appear_L->frameEvents[13] = std::bind(&Vellum::Appear_Attack, this);
	pEvent_Breath_Appear_L->frameEvents[19] = std::bind(&Vellum::AttackCollisionOff, this);
	pEvent_Breath_Appear_R->frameEvents[13] = std::bind(&Vellum::Appear_Attack, this);
	pEvent_Breath_Appear_R->frameEvents[19] = std::bind(&Vellum::AttackCollisionOff, this);

	Events* pEvent_Breath_Start_L = m_pAnimator->GetEvents(L"Vellum_Breath_Start_L");
	Events* pEvent_Breath_Start_R = m_pAnimator->GetEvents(L"Vellum_Breath_Start_R");
	pEvent_Breath_Start_L->EndEvent = std::bind(&Vellum::Play_Breath_Loop, this);
	pEvent_Breath_Start_R->EndEvent = std::bind(&Vellum::Play_Breath_Loop, this);

	Events* pEvent_Breath_Loop_L = m_pAnimator->GetEvents(L"Vellum_Breath_Loop_L");
	Events* pEvent_Breath_Loop_R = m_pAnimator->GetEvents(L"Vellum_Breath_Loop_R");
	pEvent_Breath_Loop_L->frameEvents[0] = std::bind(&Vellum::Breath_Attack, this);
	pEvent_Breath_Loop_R->frameEvents[0] = std::bind(&Vellum::Breath_Attack, this);

	Events* pEvent_Breath_Loop_End_L = m_pAnimator->GetEvents(L"Vellum_Breath_Loop_End_L");
	Events* pEvent_Breath_Loop_End_R = m_pAnimator->GetEvents(L"Vellum_Breath_Loop_End_R");
	pEvent_Breath_Loop_End_L->EndEvent = std::bind(&Vellum::SetState_Dig, this);
	pEvent_Breath_Loop_End_R->EndEvent = std::bind(&Vellum::SetState_Dig, this);

	Events* pEvent_Appear_L = m_pAnimator->GetEvents(L"Vellum_Appear_L");
	Events* pEvent_Appear_R = m_pAnimator->GetEvents(L"Vellum_Appear_R");
	pEvent_Appear_L->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_Appear_R->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_Appear_L->frameEvents[13] = std::bind(&Vellum::Appear_Attack, this);
	pEvent_Appear_L->frameEvents[19] = std::bind(&Vellum::AttackCollisionOff, this);
	pEvent_Appear_R->frameEvents[13] = std::bind(&Vellum::Appear_Attack, this);
	pEvent_Appear_R->frameEvents[19] = std::bind(&Vellum::AttackCollisionOff, this);

	Events* pEvent_LowNeck_L = m_pAnimator->GetEvents(L"Vellum_LowNeck_L");
	Events* pEvent_LowNeck_R = m_pAnimator->GetEvents(L"Vellum_LowNeck_R");
	pEvent_LowNeck_L->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_LowNeck_R->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_LowNeck_L->frameEvents[13] = std::bind(&Vellum::LowNeck_Attack, this);
	pEvent_LowNeck_L->frameEvents[19] = std::bind(&Vellum::AttackCollisionOff, this);
	pEvent_LowNeck_R->frameEvents[13] = std::bind(&Vellum::LowNeck_Attack, this);
	pEvent_LowNeck_R->frameEvents[19] = std::bind(&Vellum::AttackCollisionOff, this);

	Events* pEvent_Vellum_Attack1_L = m_pAnimator->GetEvents(L"Vellum_Attack1_L");
	Events* pEvent_Vellum_Attack1_R = m_pAnimator->GetEvents(L"Vellum_Attack1_R");
	pEvent_Vellum_Attack1_L->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_Vellum_Attack1_R->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_Vellum_Attack1_L->frameEvents[13] = std::bind(&Vellum::Appear_Attack, this);
	pEvent_Vellum_Attack1_L->frameEvents[19] = std::bind(&Vellum::AttackCollisionOff, this);
	pEvent_Vellum_Attack1_R->frameEvents[13] = std::bind(&Vellum::Appear_Attack, this);
	pEvent_Vellum_Attack1_R->frameEvents[19] = std::bind(&Vellum::AttackCollisionOff, this);

	Events* pEvent_Vellum_Attack2_L = m_pAnimator->GetEvents(L"Vellum_Attack2_L"); 
	Events* pEvent_Vellum_Attack2_R = m_pAnimator->GetEvents(L"Vellum_Attack2_R"); 
	pEvent_Vellum_Attack2_L->EndEvent = std::bind(&Vellum::End_State, this); //26
	pEvent_Vellum_Attack2_R->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_Vellum_Attack2_L->frameEvents[14] = std::bind(&Vellum::Attack2_Attack, this);
	pEvent_Vellum_Attack2_R->frameEvents[14] = std::bind(&Vellum::Attack2_Attack, this);
	pEvent_Vellum_Attack2_L->frameEvents[26] = std::bind(&Vellum::AttackCollisionOff, this);
	pEvent_Vellum_Attack2_R->frameEvents[26] = std::bind(&Vellum::AttackCollisionOff, this);

	Events* pEvent_Vellum_Attack3_L = m_pAnimator->GetEvents(L"Vellum_Attack3_L");
	Events* pEvent_Vellum_Attack3_R = m_pAnimator->GetEvents(L"Vellum_Attack3_R");
	pEvent_Vellum_Attack3_L->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_Vellum_Attack3_R->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_Vellum_Attack3_L->frameEvents[14] = std::bind(&Vellum::Attack3_Attack, this);
	pEvent_Vellum_Attack3_R->frameEvents[14] = std::bind(&Vellum::Attack3_Attack, this);
	pEvent_Vellum_Attack3_L->frameEvents[26] = std::bind(&Vellum::AttackCollisionOff, this);
	pEvent_Vellum_Attack3_R->frameEvents[26] = std::bind(&Vellum::AttackCollisionOff, this);

	Events* pEvent_Vellum_Attack4_L = m_pAnimator->GetEvents(L"Vellum_Attack4_L");
	Events* pEvent_Vellum_Attack4_R = m_pAnimator->GetEvents(L"Vellum_Attack4_R");
	pEvent_Vellum_Attack4_L->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_Vellum_Attack4_R->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_Vellum_Attack4_L->frameEvents[20] = std::bind(&Vellum::Attack4_Attack, this);
	pEvent_Vellum_Attack4_L->frameEvents[27] = std::bind(&Vellum::AttackCollisionOff, this);
	pEvent_Vellum_Attack4_R->frameEvents[20]= std::bind(&Vellum::Attack4_Attack, this);
	pEvent_Vellum_Attack4_R->frameEvents[27] = std::bind(&Vellum::AttackCollisionOff, this);

	Events* pEvent_Vellum_Dig_L = m_pAnimator->GetEvents(L"Vellum_Dig_L");
	Events* pEvent_Vellum_Dig_R = m_pAnimator->GetEvents(L"Vellum_Dig_R");
	pEvent_Vellum_Dig_L->EndEvent = std::bind(&Vellum::End_State, this);
	pEvent_Vellum_Dig_R->EndEvent = std::bind(&Vellum::End_State, this);
}

void Vellum::Appear_Attack()
{
	if (m_pAttackCollider)
	{
		float fXOffset = 20.f;
		if (!m_bRight)
			fXOffset = -fXOffset;
		m_pAttackCollider->SetPos(GetPos());
		Vec2 vSize = m_pCollider->GetSize();
		vSize.x += 30.f;
		m_pAttackCollider->SetCollisionSize(vSize);
		m_pAttackCollider->SetCollisionOffset({ fXOffset, 150.f });
		m_pAttackCollider->SetCollisionOnOff(true);
	}
}

void Vellum::LowNeck_Attack()
{
	if (m_pAttackCollider)
	{
		float fXOffset = 20.f;
		if (!m_bRight)
			fXOffset = -fXOffset;

		m_pAttackCollider->SetPos(GetPos());
		m_pAttackCollider->SetCollisionSize({ 367.f, 369.f});
		m_pAttackCollider->SetCollisionOffset({ fXOffset, 150.f });
		m_pAttackCollider->SetCollisionOnOff(true);
	}
}

void Vellum::Attack2_Attack()
{
	if (m_pAttackCollider)
	{
		float fXOffset = 850.f;
		if (!m_bRight)
			fXOffset = -fXOffset;
		m_pAttackCollider->SetPos(GetPos());
		m_pAttackCollider->SetCollisionSize({ 436.f, 379.f });
		m_pAttackCollider->SetCollisionOffset({ fXOffset, 150.f });
		m_pAttackCollider->SetCollisionOnOff(true);
	}
}

void Vellum::Attack3_Attack()
{
	if (m_pAttackCollider)
	{
		float fXOffset = 580.f;
		if (!m_bRight)
			fXOffset = -fXOffset;
		m_pAttackCollider->SetPos(GetPos());
		m_pAttackCollider->SetCollisionSize({ 400.f, 379.f });
		m_pAttackCollider->SetCollisionOffset({ fXOffset, 150.f });
		m_pAttackCollider->SetCollisionOnOff(true);
	}
}

void Vellum::Attack4_Attack()
{
	if (m_pAttackCollider)
	{
		float fXOffset = 450.f;
		if (!m_bRight)
			fXOffset = -fXOffset;
		m_pAttackCollider->SetPos(GetPos());
		m_pAttackCollider->SetCollisionSize({ 972.f, 379.f });
		m_pAttackCollider->SetCollisionOffset({ fXOffset, 150.f });
		m_pAttackCollider->SetCollisionOnOff(true);
	}
}

void Vellum::Breath_Attack()
{
	if (m_pAttackCollider)
	{
		float fXOffset = 750.f;
		if (!m_bRight)
			fXOffset = -fXOffset;
		m_pAttackCollider->SetPos(GetPos());
		m_pAttackCollider->SetCollisionSize({ 341.f, 810.f });
		m_pAttackCollider->SetCollisionOffset({ fXOffset, 0.f });
		m_pAttackCollider->SetCollisionOnOff(true);
	}
}

void Vellum::AttackCollisionOff()
{
	if (m_pAttackCollider)
	{
		m_pAttackCollider->SetCollisionOnOff(false);
		m_pAttackCollider->SetCollisionOffset(Vec2::Zero);
	}
}


void Vellum::End_State()
{
	switch (m_eVellumState)
	{
	case Vellum_State::Move:
		EndState_Move();
		break;
	case Vellum_State::Appear:
		EndState_Appear();
		break;
	case Vellum_State::LowNeck:
		EndState_Dig();
		break;
	case Vellum_State::Attack1:
		EndState_Dig();
		break;
	case Vellum_State::Attack2:
		EndState_Attack2();
		break;
	case Vellum_State::Attack3:
		EndState_Attack3();
		break;
	case Vellum_State::Attack4:
		EndState_Attack4();
		break;
	case Vellum_State::Breath:
		break;
	case Vellum_State::Dig:
		EndState_Dig();
		break;
	}
}

void Vellum::EndState_Move()
{
	float fRand = float(rand() % 15);

	if (fRand < 5.f)
		SetState_Appear();
	else if (fRand < 11.f)
		SetState_Attack1();
	else if (fRand < 15.f)
		SetState_LowNeck();
}

void Vellum::EndState_Appear()
{
	if ((m_bRight && GetPos().x > m_pTarget->GetPos().x)
		|| (!m_bRight && GetPos().x < m_pTarget->GetPos().x))
	{
		SetState_Dig();
		return;
	}

	int iRand = rand() % 2;
	m_iMaxShotCount = (rand() % 3) + 1;

	if (iRand <= 0.f)
		SetState_Attack2();
	else
		SetState_Attack3();
}

void Vellum::EndState_Attack2()
{
	if (m_iShotCount == m_iMaxShotCount)
	{
		m_iShotCount = 0;
		m_iMaxShotCount = 0;

		SetState_Dig();
	}
	else
	{
		SetState_Attack3();
	}

}

void Vellum::EndState_Attack3()
{
	if (m_iShotCount == m_iMaxShotCount)
	{
		m_iShotCount = 0;
		m_iMaxShotCount = 0;

		SetState_Dig();
	}
	else
	{
		SetState_Attack2();
	}
}

void Vellum::EndState_Attack4()
{
	SetState_Move();
}

void Vellum::EndState_Dig()
{
 	int iRand = rand() % 20;
	if (iRand < 6)
		SetState_Move();
	else if (iRand < 12)
		SetState_Move_NoAnim();
	else if (iRand < 17)
		SetState_Attack4();
	else if (m_iHp < m_iMaxHp * 0.4f)
		SetState_Breath();
	else
		SetState_Move_NoAnim();
}


void Vellum::Move()
{
	static float s_fNowTime = 0.f;

	s_fNowTime += TimeMgr::DeltaTime();

	if (s_fNowTime >= m_fMoveTime)
	{
		s_fNowTime = 0.f;
		End_State();
		return;
	}

	float fXPos = GetPos().x;
	if (m_pTarget->GetPos().x > fXPos)
		fXPos += m_fSpeed * TimeMgr::DeltaTime();
	else
		fXPos -= m_fSpeed * TimeMgr::DeltaTime();

	m_tTransform.vPos.x = fXPos;
}

void Vellum::Breath()
{
	static float s_fNowTime = 0.f;

	if (m_bTimerOn)
	{
		s_fNowTime += TimeMgr::DeltaTime();

		if (s_fNowTime >= 5.f)
		{
			s_fNowTime = 0.f;
			m_bTimerOn = false;
			if (m_bRight)
				m_pAnimator->PlayAnimation(L"Vellum_Breath_Loop_End_R", false);
			else
				m_pAnimator->PlayAnimation(L"Vellum_Breath_Loop_End_L", false);
			SoundMgr::Play(L"Vellum_Attack11");

			for (size_t i = 0; i < m_vecBreath.size(); ++i)
				m_vecBreath[i]->Play_EndAnim(m_bRight);
			AttackCollisionOff();
		}
	}
}

void Vellum::Attack_Tail()
{
	static float s_fNowTime = 0.f;

	if (m_iTailCount == 0)
		return;

	s_fNowTime += TimeMgr::DeltaTime();
	if (s_fNowTime >= m_fTailTimeGap)
	{
		s_fNowTime = 0.f;

		Tail* pTail = Instantiate<Tail>(eLayerType::LT_MONSTER);
		pTail->SetPos({ m_pTarget->GetPos().x, 410.f });
		pTail->SetOwner(this);
		pTail->PlayAnim(m_bRight);

		m_fTailTimeGap = float(rand() % 3 + 1);
		m_iTailCount--;
		m_iTailCount = max(m_iTailCount, 0);
	}
}

void Vellum::SetState_Move()
{
	float fRandTime = float(rand() % 3 + 1);
	m_fMoveTime = fRandTime;

	m_eVellumState = Vellum_State::Move;
	
	m_pAnimator->PlayAnimation(L"Vellum_Move");
}

void Vellum::SetState_Move_NoAnim()
{
	float fRandTime = float(rand() % 3 + 1); // float(rand() % 50) / 100.f);
	m_fMoveTime = fRandTime;

	m_pAnimator->SetActiveAnim(nullptr);

	m_eVellumState = Vellum_State::Move;
}

void Vellum::SetState_Appear()
{
	SoundMgr::Play(L"Vellum_Attack2");
	if (GetPos().x > m_pTarget->GetPos().x)
	{
		m_bRight = false;
		m_pAnimator->PlayAnimation(L"Vellum_Appear_L", false);
	}
	else
	{
		m_bRight = true;
		m_pAnimator->PlayAnimation(L"Vellum_Appear_R", false);
	}
	m_eVellumState = Vellum_State::Appear;

	m_iTailCount = min(m_iTailCount + rand() % 4, m_iMaxTailCount);

}

void Vellum::SetState_Attack1()
{
	SoundMgr::Play(L"Vellum_Attack1");
	if (GetPos().x < m_pTarget->GetPos().x)
	{
		m_bRight = true;
		m_pAnimator->PlayAnimation(L"Vellum_Attack1_R", false);
	}
	else
	{
		m_pAnimator->PlayAnimation(L"Vellum_Attack1_L", false);
		m_bRight = false;
	}
	m_eVellumState = Vellum_State::Attack1;

	m_iTailCount = min(m_iTailCount + rand() % 4, m_iMaxTailCount);
}

void Vellum::SetState_Attack2()
{
	m_iShotCount++;
	SoundMgr::Play(L"Vellum_Attack4");
	if (m_bRight)
		m_pAnimator->PlayAnimation(L"Vellum_Attack2_R", false);
	else
		m_pAnimator->PlayAnimation(L"Vellum_Attack2_L", false);

	m_eVellumState = Vellum_State::Attack2;

	m_iTailCount = min(m_iTailCount + 1, m_iMaxTailCount);
}

void Vellum::SetState_Attack3()
{
	m_iShotCount++;
	SoundMgr::Play(L"Vellum_Attack5");
	if (m_bRight)
		m_pAnimator->PlayAnimation(L"Vellum_Attack3_R", false);
	else
		m_pAnimator->PlayAnimation(L"Vellum_Attack3_L", false);

	m_eVellumState = Vellum_State::Attack3;

	m_iTailCount = min(m_iTailCount + 1, m_iMaxTailCount);
}

void Vellum::SetState_Attack4()
{
	SoundMgr::Play(L"Vellum_Attack8");
	if (GetPos().x < m_pTarget->GetPos().x)
	{
		m_bRight = true;
		m_pAnimator->PlayAnimation(L"Vellum_Attack4_R", false);
	}
	else
	{
		m_bRight = false;
		m_pAnimator->PlayAnimation(L"Vellum_Attack4_L", false);
	}
		
	m_eVellumState = Vellum_State::Attack4;

	m_iTailCount = min(m_iTailCount + 1, m_iMaxTailCount);
}

void Vellum::SetState_LowNeck()
{
	SoundMgr::Play(L"Vellum_Attack7");
	if (GetPos().x < m_pTarget->GetPos().x)
	{
		m_bRight = true;
		m_pAnimator->PlayAnimation(L"Vellum_LowNeck_R", false);
	}	
	else
	{
		m_bRight = false;
		m_pAnimator->PlayAnimation(L"Vellum_LowNeck_L", false);
	}

	m_eVellumState = Vellum_State::LowNeck;

	m_iTailCount = min(m_iTailCount + 1, m_iMaxTailCount);
}

void Vellum::SetState_Breath()
{
	m_eVellumState = Vellum_State::Breath;
	SoundMgr::Play(L"Vellum_Attack9");
  	SoundMgr::SetVolume(L"Vellum_Attack9", 0.6f);

	float fMinGap = fabs(m_pTarget->GetPos().x - m_fBreath_LeftX);
	float fMaxGap = fabs(m_pTarget->GetPos().x - m_fBreath_RightX);

	if (fMinGap < fMaxGap)
	{
		m_tTransform.vPos.x = m_fBreath_RightX;
		m_bRight = false;
		m_pAnimator->PlayAnimation(L"Vellum_Breath_Appear_L", false);
	}
	else
	{
		m_tTransform.vPos.x = m_fBreath_LeftX;
		m_bRight = true;
		m_pAnimator->PlayAnimation(L"Vellum_Breath_Appear_R", false);
	}

	m_eVellumState = Vellum_State::Breath;
}

void Vellum::SetState_Dig()
{
	SoundMgr::Play(L"Vellum_Attack6");
	if (m_bRight)
		m_pAnimator->PlayAnimation(L"Vellum_Dig_R", false);
	else
		m_pAnimator->PlayAnimation(L"Vellum_Dig_L", false);
	
	m_eVellumState = Vellum_State::Dig;

	m_iTailCount = min(m_iTailCount + 1, m_iMaxTailCount);
}
