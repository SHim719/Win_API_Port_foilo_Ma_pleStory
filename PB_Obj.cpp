#include "PB_Obj.h"
#include "ResourceMgr.h"
#include "HitEffect.h"
#include "Enemy.h"
#include "SoundMgr.h"


PB_Obj::PB_Obj()
{
	SetName(L"PB_Obj");
}

PB_Obj::~PB_Obj()
{
	Release();
}

void PB_Obj::Initialize()
{
	m_vOffset = Vec2(180.0f, 100.0f);
	m_iMaxHitCount = 8;
	m_iPerHitCount = 2;
	m_iMaxEnemyCount = 6;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(420.f, 200.f));

	m_pSkillTex = ResourceMgr::Find<JoTexture>(L"PhantomBlow");
	m_pHitEffect = ResourceMgr::Find<JoTexture>(L"PB_Hit");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"PhantomBlow_L", m_pSkillTex, Vec2(0.0f, 0.0f), Vec2(600.f, 400.f), Vec2::Zero,
		12, 0.07f);
	m_pAnimator->CreateAnimation(L"PhantomBlow_R", m_pSkillTex, Vec2(0.0f, 400.0f), Vec2(600.f, 400.f), Vec2::Zero,
		12, 0.07f);

	function<void()> ownerNull = [&]() ->void { m_pOwner = nullptr; };

	Events* pbEvents_L = m_pAnimator->GetEvents(L"PhantomBlow_L");
	pbEvents_L->frameEvents[8] = bind(&Collider::SetCollisionInactive, m_pCollider); 
	pbEvents_L->frameEvents[7] = ownerNull;

	Events* pbEvents_R = m_pAnimator->GetEvents(L"PhantomBlow_R");
	pbEvents_R->frameEvents[8] = bind(&Collider::SetCollisionInactive, m_pCollider);
	pbEvents_R->frameEvents[7] = ownerNull;
}

void PB_Obj::Update()
{
	if (m_pAnimator->IsEndAnim() && m_vecAttInfo.empty())
	{
		Destroy(this);
		return;
	}

	if (m_pOwner)
	{
		if (m_pOwner->isStunning())
		{
			Destroy(this);
			return;
		}
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
		if (attInfo.fNowTime >= 0.13f)
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

			SoundMgr::Play(L"PB_Hit_SFX");
			Vec2 effectPos = attInfo.vecEffectPos[attInfo.iHitCount / m_iPerHitCount - 1];
			HitEffect* pEffect = Instantiate_NoInit<HitEffect>(eLayerType::LT_EFFECT);
			pEffect->SetPos(effectPos);
			pEffect->Set_EffectTex(m_pHitEffect);
			pEffect->SetSize(Vec2(252.f, 192.f));
			pEffect->Set_SpriteLength(8);
			pEffect->SetDuration(0.06f);
			pEffect->Initialize();
		}
		++it;
	}

	if (m_pOwner)
	{
		Vec2 playerPos = m_pOwner->GetPos();
		Vec2 dir = m_pOwner->isRight() ? Vec2(1.f, 0.f) : Vec2(-1.f, 0.f);
		SetPos(playerPos + dir * m_vOffset);
	}
	
	m_pAnimator->Update();
}

void PB_Obj::LateUpdate()
{
}

void PB_Obj::Render()
{
	m_pAnimator->Render();
	m_pCollider->Render();
}

void PB_Obj::Release()
{

}

void PB_Obj::Skill_Start()
{
	if (!m_pOwner->isRight())
		m_pAnimator->PlayAnimation(L"PhantomBlow_L", false);
	else
		m_pAnimator->PlayAnimation(L"PhantomBlow_R", false);
	SoundMgr::Play(L"PB_Use");
}

void PB_Obj::OnCollisionEnter(Collider* other)
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

void PB_Obj::OnCollisionStay(Collider* other)
{
}

void PB_Obj::OnCollisionExit(Collider* other)
{
}
