#include "KF_Obj.h"
#include "ResourceMgr.h"
#include "HitEffect.h"
#include "Enemy.h"
#include "SoundMgr.h"

KF_Obj::KF_Obj()
{
	SetName(L"KF_Obj");
}

KF_Obj::~KF_Obj()
{
}

void KF_Obj::Initialize()
{
	m_vOffset = { 30.f , -200.f };

	m_iMaxEnemyCount = 10;
	m_iMaxHitCount = 14;
	m_iPerHitCount = 2;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(600.f, 600.f));	
	m_pCollider->SetCollisionInactive();

	m_pSkillTex = ResourceMgr::Find<JoTexture>(L"KarmaFury");
	m_pHitEffect = ResourceMgr::Find<JoTexture>(L"KF_Hit");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"KarmaFury", m_pSkillTex, Vec2(0.0f, 0.0f), Vec2(1840.f, 823.f), Vec2::Zero,
		24, 4, 0.07f);

	Events* pKarmaFury_Event = m_pAnimator->GetEvents(L"KarmaFury");
	pKarmaFury_Event->frameEvents[10] = bind(&Collider::SetCollisionActive, m_pCollider);
	pKarmaFury_Event->frameEvents[13] = bind(&Collider::SetCollisionInactive, m_pCollider);
}

void KF_Obj::Update()
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
		if (attInfo.fNowTime >= 0.08f)
		{
			attInfo.fNowTime = 0.f;
			if (attInfo.iHitCount >= m_iMaxHitCount)
			{
				it = m_vecAttInfo.erase(it);
				continue;
			}

			for (int i = 0; i < m_iPerHitCount; ++i)
			{
				HitInfo hitInfo = { 50000, attInfo.iHitCount, false };
				attInfo.pHitObj->Hit(hitInfo);
				attInfo.iHitCount++;
			}

			SoundMgr::Play(L"KF_Hit_SFX");
			Vec2 effectPos = attInfo.vecEffectPos[attInfo.iHitCount / m_iPerHitCount - 1];
			HitEffect* pEffect = Instantiate_NoInit<HitEffect>(eLayerType::LT_EFFECT);
			pEffect->SetPos(effectPos);
			pEffect->Set_EffectTex(m_pHitEffect);
			pEffect->SetSize(Vec2(244.f, 192.f));
			pEffect->Set_SpriteLength(8);
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
}

void KF_Obj::Render()
{
	m_pAnimator->Render();
	m_pCollider->Render();
}

void KF_Obj::Release()
{
}

void KF_Obj::Skill_Start()
{
	m_pAnimator->PlayAnimation(L"KarmaFury", false);
	SoundMgr::Play(L"KF_Use");
}

void KF_Obj::OnCollisionEnter(Collider* other)
{
	push_AttackInfo(other);
	/*if (m_vecAttInfo.size() >= m_iMaxEnemyCount) return;

	AttackInfo info{};
	info.pHitObj = dynamic_cast<Enemy*>(other->GetOwner());

	if (info.pHitObj == nullptr)
		return;

	int iHitCount = m_iMaxHitCount / m_iPerHitCount;
	for (int i = 0; i < iHitCount; ++i)
		info.vecEffectPos.push_back(GetOverlappedRectPos(other));

	info.iHitCount = 0;
	info.fNowTime = 100.f;

	m_vecAttInfo.push_back(info);*/
}

void KF_Obj::OnCollisionStay(Collider* other)
{
}

void KF_Obj::OnCollisionExit(Collider* other)
{
}
