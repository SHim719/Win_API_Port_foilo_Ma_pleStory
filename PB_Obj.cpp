#include "PB_Obj.h"
#include "ResourceMgr.h"
#include "joObject.h"
#include "HitEffect.h"


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
	m_iMaxEnemyCount = 6;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(420.f, 200.f));

	m_pSkillTex = ResourceMgr::Find<JoTexture>(L"PhantomBlow");
	m_pHitEffect = ResourceMgr::Find<JoTexture>(L"PB_Hit");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"PhantomBlow_L", m_pSkillTex, Vec2(0.0f, 0.0f), Vec2(600.f, 400.f), Vec2::Zero,
		12, 0.06f);
	m_pAnimator->CreateAnimation(L"PhantomBlow_R", m_pSkillTex, Vec2(0.0f, 400.0f), Vec2(600.f, 400.f), Vec2::Zero,
		12, 0.06f);

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
	if (m_pAnimator->IsEndAnim() && m_vecHitInfo.empty())
	{
		Destroy(this);
		return;
	}

	for (auto it = m_vecHitInfo.begin(); it != m_vecHitInfo.end();)
	{
		HitInfo& info = *it;
		info.tTimer.fNowTime += TimeMgr::DeltaTime();
		if (info.tTimer.Time_Elapsed(0.07f))
		{
			if (info.iHitCount >= m_iMaxHitCount)
			{
				it = m_vecHitInfo.erase(it);
				continue;
			}

			/*Hit_Status hitInfo = { 500235, ah.iHitCount, false, GetOwner() };
			static_cast<Boss*>(ah.pObj)->Hit(hitInfo);*/

			Vec2 effectPos = info.m_vecEffectPos[info.iHitCount];
			HitEffect* pEffect = Instantiate<HitEffect>(eLayerType::LT_EFFECT);
			pEffect->SetPos(effectPos);
			info.iHitCount++;
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
	if (m_vecHitInfo.size() >= m_iMaxEnemyCount) return;

	HitInfo info{};
	info.pObj = other->GetOwner();
	for (int i = 0; i < m_iMaxHitCount; ++i)
	{
		info.m_vecEffectPos.push_back(GetOverlappedRectPos(other));
	}
	info.iHitCount = 0;

	m_vecHitInfo.push_back(info);
}

void PB_Obj::OnCollisionStay(Collider* other)
{
}

void PB_Obj::OnCollisionExit(Collider* other)
{
}
