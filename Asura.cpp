#include "Asura.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "AS_Obj.h"

Asura::Asura()
	: m_bPrevRight(false)
{
	SetName(L"¾Æ¼ö¶ó");
}

Asura::~Asura()
{
}

void Asura::Initialize()
{
	m_pSkillIconTex = ResourceMgr::Load<JoTexture>(L"Asura_Icon", L"Resources/UI/Skill/Asura/icon.png");
	m_pSkillIconDisabledTex = ResourceMgr::Load<JoTexture>(L"Asura_Icon_Disabled", L"Resources/UI/Skill/Asura/iconDisabled.png");
	m_pIconTex = m_pSkillIconDisabledTex;
}

void Asura::Render(const Vec2& vLeftTop)
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

void Asura::Key_Check(const eKeyCode& _key)
{
	if (KeyMgr::GetKeyDown(_key))
		Execution();
	else if (KeyMgr::GetKey(_key))
		Execution_Loop();
	else if (KeyMgr::GetKeyUp(_key))
		Execution_End();
}

void Asura::Execution()
{
	if (m_pOwner == nullptr)
		return;
	if (Player::PlayerState::Idle != m_pOwner->GetPlayerState()
		&& Player::PlayerState::Walk != m_pOwner->GetPlayerState())
		return;

	unsigned char restriction = 0;
	m_pOwner->SetState_Channeling(restriction);

	AS_Obj* pObj = Instantiate<AS_Obj>(eLayerType::LT_EFFECT);
	pObj->SetOwner(m_pOwner);
	pObj->Skill_Start();


	if (!m_pOwner->isRight())
	{
		m_pOwner->GetAnimator()->PlayAnimation(L"Asura_L", true);
		m_bPrevRight = false;
	}
	else
	{
		m_pOwner->GetAnimator()->PlayAnimation(L"Asura_R", true);
		m_bPrevRight = true;
	}
}

void Asura::Execution_Loop()
{
	if (!m_pOwner->isChanneling())
		return;

	if (!m_pOwner->isRight() && m_bPrevRight)
	{
		m_pOwner->GetAnimator()->PlayAnimation(L"Asura_L", true);
		m_bPrevRight = false;
	}
	else if (m_pOwner->isRight() && !m_bPrevRight)
	{
		m_pOwner->GetAnimator()->PlayAnimation(L"Asura_R", true);
		m_bPrevRight = true;
	}
}

void Asura::Execution_End()
{
	m_pOwner->Skill_End();
}
