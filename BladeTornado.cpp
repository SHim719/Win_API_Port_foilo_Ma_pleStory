#include "BladeTornado.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "BT_Obj.h"

BladeTornado::BladeTornado()
{
	SetName(L"블레이드 토네이도");
}

BladeTornado::~BladeTornado()
{
}

void BladeTornado::Initialize()
{
	m_pSkillIconTex = ResourceMgr::Load<JoTexture>(L"BladeTornado_Icon", L"Resources/UI/Skill/BladeTornado/icon.png");
	m_pSkillIconDisabledTex = ResourceMgr::Load<JoTexture>(L"BladeTornado_Icon_Disabled", L"Resources/UI/Skill/BladeTornado/iconDisabled.png");
	m_pIconTex = m_pSkillIconDisabledTex;
}

void BladeTornado::Render(const Vec2& vLeftTop)
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

void BladeTornado::Key_Check(const eKeyCode& _key)
{
	if (KeyMgr::GetKeyDown(_key))
		Execution();
}

void BladeTornado::Execution()
{
	if (m_pOwner == nullptr)
		return;
	if (Player::PlayerState::Idle != m_pOwner->GetPlayerState()
		&& Player::PlayerState::Walk != m_pOwner->GetPlayerState()
		&& Player::PlayerState::Air != m_pOwner->GetPlayerState())
		return;

	unsigned char restriction = 1 | (1 << 1);
	m_pOwner->SetState_Channeling(restriction);

	BT_Obj* pObj = Instantiate<BT_Obj>(eLayerType::LT_EFFECT);

	if (!m_pOwner->isRight())
	{
		m_pOwner->GetAnimator()->PlayAnimation(L"BladeTornado_L", false);
		pObj->SetDir(-1.f);
	}	
	else
	{
		m_pOwner->GetAnimator()->PlayAnimation(L"BladeTornado_R", false);
		pObj->SetDir(1.f);
	}
		
	if (m_pOwner->GetRigidbody()->IsGround())
		m_pOwner->GetRigidbody()->SetVelocityX(0.f);

	pObj->SetOwner(m_pOwner);
	pObj->Skill_Start();
}
