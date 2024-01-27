#include "BS_Obj.h"
#include "ResourceMgr.h"
#include "HitEffect.h"
#include "Enemy.h"
#include "SoundMgr.h"

BS_Obj::BS_Obj()
	: m_vDir{}
	, m_fGap(0.f)
	, m_fXOffset(0.f)
{
}

BS_Obj::~BS_Obj()
{
}

void BS_Obj::Initialize()
{
	m_vOffset = { 250.f , -100.f };

	m_iMaxEnemyCount = 10;
	m_iMaxHitCount = 3;
	m_iPerHitCount = 3;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(470.f, 250.f));

	JoTexture* pSkillTex_L = ResourceMgr::Find<JoTexture>(L"BladeStorm_L");
	JoTexture* pSkillTex_R = ResourceMgr::Find<JoTexture>(L"BladeStorm_R");
	m_pHitEffect = ResourceMgr::Find<JoTexture>(L"BS_Hit");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"BladeStorm_L", pSkillTex_L, Vec2(0.0f, 0.0f), Vec2(906.f, 481.f), Vec2::Zero,
		11, 6, 0.07f);
	m_pAnimator->CreateAnimation(L"BladeStorm_R", pSkillTex_R, Vec2(0.0f, 0.0f), Vec2(906.f, 481.f), Vec2::Zero,
		11, 6, 0.07f);

	m_fGap = 0.1f;

	m_fXOffset = 130.f;
}

void BS_Obj::Update()
{
	if (m_pOwner->isChanneling() == false)
	{
		SoundMgr::Stop(L"BS_Loop");
		Destroy(this);
		return;
	}

	if (m_pOwner->isRight() && m_vDir.x < 0.f)
	{
		m_vDir.x = 1.f;
		m_pCollider->SetOffset(Vec2(-m_fXOffset, 0.f));
		m_pAnimator->PlayAnimation(L"BladeStorm_R");
	}
	else if (!m_pOwner->isRight() && m_vDir.x > 0.f)
	{
		m_vDir.x = -1.f;
		m_pCollider->SetOffset(Vec2(m_fXOffset, 0.f));
		m_pAnimator->PlayAnimation(L"BladeStorm_L");
	}

	if (m_pOwner)
	{
		m_tTransform.vPos = m_pOwner->GetPos();
		m_tTransform.vPos.x += m_vDir.x * m_vOffset.x;
		m_tTransform.vPos.y += m_vOffset.y;
	}

	for (auto it = m_vecAttInfo.begin(); it != m_vecAttInfo.end();)
	{
		AttackInfo& attInfo = *it;

		if (static_cast<Enemy*>(attInfo.pHitObj)->IsActive() == false
			|| static_cast<Enemy*>(attInfo.pHitObj)->GetCollider()->IsCollisionOn() == false)
		{
			it = m_vecAttInfo.erase(it);
			continue;
		}
		attInfo.fNowTime += TimeMgr::DeltaTime();
		if (attInfo.fNowTime >= 0.14f)
		{
			attInfo.fNowTime = 0.f;
			attInfo.iHitCount %= 15;

			for (int i = 0; i < m_iPerHitCount; ++i)
			{
				HitInfo hitInfo = { 50000, attInfo.iHitCount, false };
				attInfo.pHitObj->Hit(hitInfo);
				attInfo.iHitCount++;
			}

			SoundMgr::Play(L"BS_Hit_SFX");
			Vec2 effectPos = attInfo.vecEffectPos[m_iMaxHitCount / m_iPerHitCount - 1] + Vec2(float(rand() % 50 - 100), float(rand() % 50 - 100));
			HitEffect* pEffect = Instantiate_NoInit<HitEffect>(eLayerType::LT_EFFECT);
			pEffect->SetPos(effectPos);
			pEffect->Set_EffectTex(m_pHitEffect);
			pEffect->SetSize(Vec2(475.f, 200.f));
			pEffect->Set_SpriteLength(7);
			pEffect->SetDuration(0.06f);
			pEffect->Initialize();
		}
		++it;
	}

	m_pAnimator->Update();
}

void BS_Obj::Render()
{
	m_pAnimator->Render();
	m_pCollider->Render();
}

void BS_Obj::Release()
{
}

void BS_Obj::Skill_Start()
{
	SoundMgr::Play(L"BS_Loop");
	if (m_pOwner->isRight())
	{
		m_vDir.x = 1.f;
		m_pCollider->SetOffset(Vec2(-m_fXOffset, 0.f));
		m_pAnimator->PlayAnimation(L"BladeStorm_R");
	}
	else
	{
		m_vDir.x = -1.f;
		m_pCollider->SetOffset(Vec2(m_fXOffset, 0.f));
		m_pAnimator->PlayAnimation(L"BladeStorm_L");
	}
}

void BS_Obj::OnCollisionEnter(Collider* other)
{
	push_AttackInfo(other);
}

void BS_Obj::OnCollisionStay(Collider* other)
{
}

void BS_Obj::OnCollisionExit(Collider* other)
{
	auto it = std::find_if(m_vecAttInfo.begin(), m_vecAttInfo.end(), [&](AttackInfo& _info)-> bool
		{
			return static_cast<Enemy*>(other->GetOwner()) == _info.pHitObj;
		});

	if (it != m_vecAttInfo.end())
	{
		m_vecAttInfo.erase(it);
	}
}
