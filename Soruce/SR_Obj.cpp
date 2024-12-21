#include "SR_Obj.h"
#include "ResourceMgr.h"
#include "HitEffect.h"
#include "Enemy.h"
#include "SoundMgr.h"

SR_Obj::SR_Obj()
{
}

SR_Obj::~SR_Obj()
{
	Safe_Delete<Animator*>(m_pBackAnimator);
}

void SR_Obj::Initialize()
{
	m_vOffset = { 30.f , -100.f };

	m_iMaxEnemyCount = 10;
	m_iMaxHitCount = 18;
	m_iPerHitCount = 3;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(550.f, 550.f));
	m_pCollider->SetCollisionInactive();

	m_pSkillTex = ResourceMgr::Find<JoTexture>(L"SuddenRaid_Front");
	m_pBackTex = ResourceMgr::Find<JoTexture>(L"SuddenRaid_Back");
	m_pHitEffect = ResourceMgr::Find<JoTexture>(L"SR_Hit");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"SuddenRaid_Front", m_pSkillTex, Vec2(0.0f, 0.0f), Vec2(880.f, 637.f), Vec2::Zero,
		29, 8, 0.05f);

	m_pBackAnimator = new Animator;
	m_pBackAnimator->SetOwner(this);
	m_pBackAnimator->CreateAnimation(L"SuddenRaid_Back", m_pBackTex, Vec2(0.0f, 0.0f), Vec2(1060.f, 727.f), Vec2::Zero,
		31, 7, 0.05f);

	Events* pSuddenRaid_Event = m_pAnimator->GetEvents(L"SuddenRaid_Front");
	pSuddenRaid_Event->frameEvents[11] = bind(&Collider::SetCollisionActive, m_pCollider);
	pSuddenRaid_Event->frameEvents[15] = bind(&Collider::SetCollisionInactive, m_pCollider);
}

void SR_Obj::Update()
{
	if (m_pAnimator->IsEndAnim() && m_vecAttInfo.empty())
	{
		Destroy(this);
		return;
	}

	for (auto it = m_vecAttInfo.begin(); it != m_vecAttInfo.end();)
	{
		AttackInfo& attInfo = *it;
		if (static_cast<Enemy*>(attInfo.pHitObj)->IsActive() == false)
		{
			it = m_vecAttInfo.erase(it);
			continue;
		}

		attInfo.fNowTime += TimeMgr::DeltaTime();
		if (attInfo.fNowTime >= 0.12f)
		{
			attInfo.fNowTime = 0.f;
			if (attInfo.iHitCount >= m_iMaxHitCount)
			{
				it = m_vecAttInfo.erase(it);
				continue;
			}

			for (int i = 0; i < m_iPerHitCount; ++i)
			{
				int iDamage = generateRandomNumber(3, 6);
				HitInfo hitInfo = { iDamage, attInfo.iHitCount, true };
				attInfo.pHitObj->Hit(hitInfo);
				attInfo.iHitCount++;
			}

			SoundMgr::Play(L"SR_Hit_SFX");
			Vec2 effectPos = attInfo.vecEffectPos[attInfo.iHitCount / m_iPerHitCount - 1];
			HitEffect* pEffect = Instantiate_NoInit<HitEffect>(eLayerType::LT_EFFECT);
			pEffect->SetPos(effectPos);
			pEffect->Set_EffectTex(m_pHitEffect);
			pEffect->SetSize(Vec2(276.f, 252.f));
			pEffect->Set_SpriteLength(6);
			pEffect->SetDuration(0.05f);
			pEffect->Initialize();
		}
		++it;
	}

	if (m_pOwner)
	{
		Vec2 playerPos = m_pOwner->GetPos();
		SetPos(playerPos + m_vOffset);
	}

	m_pAnimator->Update();
	m_pBackAnimator->Update();
}

void SR_Obj::Render()
{
	m_pBackAnimator->Render();
	m_pAnimator->Render();
}

void SR_Obj::Release()
{
}

void SR_Obj::Skill_Start()
{
	m_pAnimator->PlayAnimation(L"SuddenRaid_Front", false);
	m_pBackAnimator->PlayAnimation(L"SuddenRaid_Back", false);
	SoundMgr::Play(L"SR_Use");
}

void SR_Obj::OnCollisionEnter(Collider* other)
{
	push_AttackInfo(other);
}

void SR_Obj::OnCollisionStay(Collider* other)
{
}

void SR_Obj::OnCollisionExit(Collider* other)
{
}
