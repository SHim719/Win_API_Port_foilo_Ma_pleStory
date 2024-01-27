#include "BladeStorm.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "BS_Obj.h"


BladeStorm::BladeStorm()
	: m_bPrevRight(false)
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

}

void BladeStorm::Render(const Vec2& vLeftTop)
{
	JoTexture* pRenderTex = nullptr;
	if (m_fCooltime == 0.f)
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

	unsigned char restriction = 1 << 1;
	m_pOwner->SetState_Channeling(restriction);

	BS_Obj* pObj = Instantiate<BS_Obj>(eLayerType::LT_EFFECT);
	pObj->SetOwner(m_pOwner);
	pObj->Skill_Start();


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
	m_pOwner->Skill_End();
}
