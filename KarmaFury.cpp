#include "KarmaFury.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "KF_Obj.h"

KarmaFury::KarmaFury()
{
	SetName(L"카르마 퓨리");
}

KarmaFury::~KarmaFury()
{
}

void KarmaFury::Initialize()
{
	m_pSkillIconTex = ResourceMgr::Load<JoTexture>(L"KarmaFury_Icon", L"Resources/UI/Skill/KarmaFury/icon.png");
	m_pSkillIconDisabledTex = ResourceMgr::Load<JoTexture>(L"KarmaFury_Icon_Disabled", L"Resources/UI/Skill/KarmaFury/iconDisabled.png");
	m_pIconTex = m_pSkillIconDisabledTex;
}

void KarmaFury::Render(const Vec2& vLeftTop)
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

void KarmaFury::Key_Check(const eKeyCode& _key)
{
	if (KeyMgr::GetKeyDown(_key))
	{
		Execution();
	}
}

void KarmaFury::Execution()
{
	if (m_pOwner == nullptr)
		return;
	if (Player::PlayerState::Idle != m_pOwner->GetPlayerState()
		&& Player::PlayerState::Walk != m_pOwner->GetPlayerState()
		&& Player::PlayerState::Air != m_pOwner->GetPlayerState())
		return;

	unsigned char restriction = 1 | (1 << 1); // NoMove, NoJump
	m_pOwner->SetState_Channeling(restriction);

	if (!m_pOwner->isRight())
		m_pOwner->GetAnimator()->PlayAnimation(L"KarmaFury_L", false);
	else
		m_pOwner->GetAnimator()->PlayAnimation(L"KarmaFury_R", false);

	if (m_pOwner->GetRigidbody()->IsGround())
		m_pOwner->GetRigidbody()->SetVelocityX(0.f);


	KF_Obj* pObj = Instantiate<KF_Obj>(eLayerType::LT_EFFECT);
	pObj->SetOwner(m_pOwner);
	pObj->Skill_Start();
}


