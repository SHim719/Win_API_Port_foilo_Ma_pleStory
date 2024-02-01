#include "SuddenRaid.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "SR_Obj.h"

void SuddenRaid::Initialize()
{
	SetName(L"써든 레이드");
	m_pSkillIconTex = ResourceMgr::Load<JoTexture>(L"SuddenRaid_Icon", L"Resources/UI/Skill/SuddenRaid/icon.png");
	m_pSkillIconDisabledTex = ResourceMgr::Load<JoTexture>(L"SuddenRaid_Icon_Disabled", L"Resources/UI/Skill/SuddenRaid/iconDisabled.png");
	m_pIconTex = m_pSkillIconDisabledTex;

	m_fCooltime = 10.f;

	m_iUseMp = 500;
}

void SuddenRaid::Render(const Vec2& vLeftTop)
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

void SuddenRaid::Key_Check(const eKeyCode& _key)
{
	if (m_fNowTime > 0.f)
	{
		m_fNowTime -= TimeMgr::DeltaTime_NoScale();
		if (m_fNowTime <= 0.f)
			m_fNowTime = 0.f;
		return;
	}

	if (KeyMgr::GetKeyDown(_key))
		Execution();
}

void SuddenRaid::Execution()
{
	if (m_pOwner == nullptr)
		return;
	if (Player::PlayerState::Idle != m_pOwner->GetPlayerState()
		&& Player::PlayerState::Walk != m_pOwner->GetPlayerState()
		&& Player::PlayerState::Air != m_pOwner->GetPlayerState())
		return;

	if (m_pOwner->Check_Mp(m_iUseMp) == false)
		return;

	m_fNowTime = m_fCooltime;

	unsigned char restriction = 1 | (1 << 1); // NoMove, NoJump
	m_pOwner->SetState_Channeling(restriction);

	if (!m_pOwner->isRight())
		m_pOwner->GetAnimator()->PlayAnimation(L"SuddenRaid_L", false);
	else
		m_pOwner->GetAnimator()->PlayAnimation(L"SuddenRaid_R", false);

	if (m_pOwner->GetRigidbody()->IsGround())
		m_pOwner->GetRigidbody()->SetVelocityX(0.f);


	SR_Obj* pObj = Instantiate<SR_Obj>(eLayerType::LT_EFFECT);
	pObj->SetOwner(m_pOwner);
	pObj->Skill_Start();
}
