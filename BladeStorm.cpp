#include "BladeStorm.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "BS_Obj.h"


BladeStorm::BladeStorm()
	: m_bPrevRight(false)
	, m_fMaxDuration(0.f)
	, m_fNowDuration(0.f)
	, m_fMpCheckGap(0.f)
{
	SetName(L"블레이드 스톰");
}

BladeStorm::~BladeStorm()
{
}

void BladeStorm::Initialize()
{
	m_pSkillIconTex = ResourceMgr::Load<JoTexture>(L"BladeStorm_Icon", L"Resources/UI/Skill/BladeStorm/icon.png");
	m_pSkillIconDisabledTex = ResourceMgr::Load<JoTexture>(L"BladeStorm_Icon_Disabled", L"Resources/UI/Skill/BladeStorm/iconDisabled.png");
	m_pIconTex = m_pSkillIconDisabledTex;

	m_fMaxDuration = 5.f;
	m_fCooltime = 20.f; 
	m_iUseMp = 100;
}

void BladeStorm::Render(const Vec2& vLeftTop)
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

void BladeStorm::Key_Check(const eKeyCode& _key)
{
	if (!m_bUsingSkill)
	{
		if (m_fNowTime > 0.f)
		{
			m_fNowTime -= TimeMgr::DeltaTime_NoScale();
			if (m_fNowTime <= 0.f)
				m_fNowTime = 0.f;
			return;
		}
	}
	
	if (KeyMgr::GetKeyDown(_key))
		Execution();
	else if (KeyMgr::GetKey(_key))
		Execution_Loop();
	else if (KeyMgr::GetKeyUp(_key))
		Execution_End();
}

void BladeStorm::Execution()
{
	if (m_pOwner == nullptr)
		return;
	if (Player::PlayerState::Idle != m_pOwner->GetPlayerState()
		&& Player::PlayerState::Walk != m_pOwner->GetPlayerState())
		return;

	m_fNowTime = m_fCooltime;
	m_fNowDuration = 0.f;
	m_fMpCheckGap = 0.f;
	m_bUsingSkill = true;

	unsigned char restriction = 1 << 1;
	m_pOwner->SetState_Channeling(restriction);

	BS_Obj* pObj = Instantiate<BS_Obj>(eLayerType::LT_EFFECT);
	pObj->SetOwner(m_pOwner);
	pObj->Skill_Start();
	pObj->SetDuration(m_fMaxDuration);

	if (!m_pOwner->isRight())
	{
		m_pOwner->GetAnimator()->PlayAnimation(L"BladeStorm_L", true);
		m_bPrevRight = false;
	}
	else
	{
		m_pOwner->GetAnimator()->PlayAnimation(L"BladeStorm_R", true);
		m_bPrevRight = true;
	}
}

void BladeStorm::Execution_Loop()
{
	if (!m_pOwner->isChanneling())
		return;

	m_fMpCheckGap += TimeMgr::DeltaTime();
	if (m_fMpCheckGap >= 1.f)
	{
		m_fMpCheckGap = 0.f;
		if (m_pOwner->Check_Mp(m_iUseMp) == false)
		{
			Execution_End();
			return;
		}	
	}
		
	m_fNowDuration += TimeMgr::DeltaTime();
	if (m_fNowDuration >= m_fMaxDuration)
	{
		Execution_End();
		return;
	}
		
	if (!m_pOwner->isRight() && m_bPrevRight)
	{
		m_pOwner->GetAnimator()->PlayAnimation(L"BladeStorm_L", true);
		m_bPrevRight = false;
	}
	else if (m_pOwner->isRight() && !m_bPrevRight)
	{
		m_pOwner->GetAnimator()->PlayAnimation(L"BladeStorm_R", true);
		m_bPrevRight = true;
	}
}

void BladeStorm::Execution_End()
{
	if (m_bUsingSkill)
	{
		m_pOwner->Skill_End();
		m_bUsingSkill = false;
	}
}
