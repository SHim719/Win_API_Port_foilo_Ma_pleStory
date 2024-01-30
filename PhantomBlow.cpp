#include "PhantomBlow.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "PB_Obj.h"
#include "TimeMgr.h"


PhantomBlow::PhantomBlow()
{
	SetName(L"ÆÒÅÒ ºí·Î¿ì");
}

PhantomBlow::~PhantomBlow()
{
}

void PhantomBlow::Initialize()
{
	m_pSkillIconTex = ResourceMgr::Load<JoTexture>(L"PhantomBlow_Icon", L"Resources/UI/Skill/PhantomBlow/icon.png");
	m_pSkillIconDisabledTex = ResourceMgr::Load<JoTexture>(L"PhantomBlow_Icon_Disabled", L"Resources/UI/Skill/PhantomBlow/iconDisabled.png");
	m_pIconTex = m_pSkillIconDisabledTex;
}

void PhantomBlow::Render(const Vec2& vLeftTop)
{
	JoTexture* pRenderTex = nullptr;
	if (m_fNowTime == 0.f)
		pRenderTex = m_pSkillIconTex;
	else
		pRenderTex = m_pSkillIconDisabledTex;

	RenderMgr::RenderImage(pRenderTex
		, vLeftTop.x
		, vLeftTop.y
		, vLeftTop.x + 32.f
		, vLeftTop.y + 32.f);
}

void PhantomBlow::Key_Check(const eKeyCode& _key)
{
	if (KeyMgr::GetKeyDown(_key))
	{
		Execution();
	}
}

void PhantomBlow::Execution()
{
	if (m_pOwner == nullptr)
		return;
	if (Player::PlayerState::Idle != m_pOwner->GetPlayerState()
		&& Player::PlayerState::Walk != m_pOwner->GetPlayerState()
		&& Player::PlayerState::Air != m_pOwner->GetPlayerState())
		return;

	unsigned char restriction = 1 | (1 << 1);
	m_pOwner->SetState_Channeling(restriction);

	if (!m_pOwner->isRight())
		m_pOwner->GetAnimator()->PlayAnimation(L"PhantomBlow_L", false);
	else
		m_pOwner->GetAnimator()->PlayAnimation(L"PhantomBlow_R", false);

	if (m_pOwner->GetRigidbody()->IsGround())
		m_pOwner->GetRigidbody()->SetVelocityX(0.f);


	PB_Obj* pObj = Instantiate<PB_Obj>(eLayerType::LT_EFFECT);
	pObj->SetOwner(m_pOwner);
	pObj->Skill_Start();
}
