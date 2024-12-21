#include "BT_Obj.h"
#include "ResourceMgr.h"
#include "HitEffect.h"
#include "Enemy.h"
#include "SoundMgr.h"
#include "TimeMgr.h"

BT_Obj::BT_Obj()
	: m_pLoopTex(nullptr)
	, m_fSpeed(0.f)
	, m_fMoveDis(0.f)
	, m_fNowMoveDis(0.f)
	, m_fDir(0.f)
	, m_fLoopTime(0.f)
	, m_bLooping(false)
	, m_fNowTime(0.f)
{
	SetName(L"BT_Obj");
}

BT_Obj::~BT_Obj()
{
}

void BT_Obj::Initialize()
{
	m_vOffset = { 0.f , -240.f };

	m_iMaxEnemyCount = 10;
	m_iMaxHitCount = 10;
	m_iPerHitCount = 1;

	m_fSpeed = 800.f;
	m_fMoveDis = 500.f;

	m_fLoopTime = 2.f;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(300.f, 450.f));
	m_pCollider->SetOffset(Vec2(0.f, 40.f));

	m_pSkillTex = ResourceMgr::Find<JoTexture>(L"BladeTornado_Create");
	m_pLoopTex = ResourceMgr::Find<JoTexture>(L"BladeTornado_Loop");
	m_pHitEffect = ResourceMgr::Find<JoTexture>(L"BT_Hit");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"BladeTornado_Create", m_pSkillTex, Vec2(0.0f, 0.0f), Vec2(592.f, 616.f), Vec2::Zero,
		20, 7, 0.05f);
	m_pAnimator->CreateAnimation(L"BladeTornado_Loop", m_pLoopTex, Vec2(0.0f, 0.0f), Vec2(424.f, 522.f), Vec2::Zero,
		12, 0.07f);

	Events* pBT_Create_Event = m_pAnimator->GetEvents(L"BladeTornado_Create");
	pBT_Create_Event->EndEvent = std::bind(&BT_Obj::Play_LoopAnim, this);
}

void BT_Obj::Update()
{
	if (m_bLooping)
	{
		m_fNowTime += TimeMgr::DeltaTime();
		if (m_fNowMoveDis <= m_fMoveDis)
		{
			m_fNowMoveDis += m_fSpeed * TimeMgr::DeltaTime();
			Vec2 vNextPos = m_tTransform.vPos + Vec2(m_fDir, 0.f) * m_fSpeed * TimeMgr::DeltaTime();
			SetPos(vNextPos);
		}

		if (m_fNowTime >= m_fLoopTime)
		{
			m_pCollider->SetCollisionInactive();
			if (m_pAnimator->GetAlpha() == 0.f && m_vecAttInfo.empty())
			{
				SoundMgr::Stop(L"BT_Loop");
				Destroy(this);
			}
			else
				m_pAnimator->AddAlpha(-1.5f * TimeMgr::DeltaTime());
		}
	}
	else
	{
		Vec2 vPos = const_cast<Vec2&>(m_pOwner->GetPos()) + m_vOffset;
		SetPos(vPos);
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
				int iDamage = generateRandomNumber(2, 6);
				bool isCritical = Calc_Critical();
				iDamage = isCritical ? int(float(iDamage) * 1.3f) : iDamage;
				HitInfo hitInfo = { iDamage, attInfo.iHitCount, isCritical };
				attInfo.pHitObj->Hit(hitInfo);
				attInfo.iHitCount++;
			}

			SoundMgr::Play(L"BT_Hit_SFX");
			Vec2 effectPos = attInfo.vecEffectPos[attInfo.iHitCount / m_iPerHitCount - 1];
			HitEffect* pEffect = Instantiate_NoInit<HitEffect>(eLayerType::LT_EFFECT);
			pEffect->SetPos(effectPos);
			pEffect->Set_EffectTex(m_pHitEffect);
			pEffect->SetSize(Vec2(300.f, 312.f));
			pEffect->Set_SpriteLength(7);
			pEffect->SetDuration(0.05f);
			pEffect->Initialize();
		}
		++it;
	}

	m_pAnimator->Update();
}

void BT_Obj::Render()
{
	m_pAnimator->Render();
	//m_pCollider->Render();
}

void BT_Obj::Release()
{
}

void BT_Obj::Skill_Start()
{
	SoundMgr::Play(L"BT_Use");
	m_pAnimator->PlayAnimation(L"BladeTornado_Create", false);
}

void BT_Obj::OnCollisionEnter(Collider* other)
{
	push_AttackInfo(other);
}

void BT_Obj::OnCollisionStay(Collider* other)
{
	auto it = std::find_if(m_vecAttInfo.begin(), m_vecAttInfo.end(), [&](AttackInfo& _info)-> bool
		{
			return static_cast<Enemy*>(other->GetOwner()) == _info.pHitObj;
		});

	if (it == m_vecAttInfo.end())
	{
		push_AttackInfo(other);
	}
}

void BT_Obj::OnCollisionExit(Collider* other)
{
	
}

void BT_Obj::Play_LoopAnim()
{
	SoundMgr::Play(L"BT_Loop");
	m_pOwner = nullptr;
	m_pAnimator->PlayAnimation(L"BladeTornado_Loop", true);
	m_bLooping = true;
	m_tTransform.vPos.y += 40.f;
	m_pCollider->SetOffset(Vec2::Zero);
}
