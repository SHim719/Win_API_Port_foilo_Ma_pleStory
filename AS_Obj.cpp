#include "AS_Obj.h"
#include "ResourceMgr.h"
#include "HitEffect.h"
#include "Enemy.h"
#include "SoundMgr.h"

AS_Obj::AS_Obj()
	: m_fGap(0.f)
	, m_fXOffset(0.f)
	, m_pBottomAnimator(nullptr)
	, m_fDuration(0.f)
	, m_fNowTime(0.f)
{
}

AS_Obj::~AS_Obj()
{
	Release();
}

void AS_Obj::Initialize()
{
	m_vOffset = { 0.f , -100.f };

	m_iMaxEnemyCount = 10;
	m_iMaxHitCount = 3;
	m_iPerHitCount = 3;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(470.f, 250.f));

	m_pSkillTex = ResourceMgr::Find<JoTexture>(L"Asura_Loop");
	m_pBottomTex = ResourceMgr::Find<JoTexture>(L"Asura_Bottom");
	m_pHitEffect = ResourceMgr::Find<JoTexture>(L"AS_Hit");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"Asura", m_pSkillTex, Vec2(0.0f, 0.0f), Vec2(779.f, 591.f), Vec2::Zero,
		10, 0.07f);


	m_pBottomAnimator = new Animator;
	m_pBottomAnimator->SetOwner(this);
	m_pBottomAnimator->CreateAnimation(L"Asura_Bottom", m_pBottomTex, Vec2(0.0f, 0.0f), Vec2(364.f, 106.f), Vec2(0.f, 100.f),
		10, 0.07f);

	m_fGap = 0.1f;

	//m_fXOffset = 130.f;
}

void AS_Obj::Update()
{
	m_fNowTime += TimeMgr::DeltaTime();

	if (m_pOwner->isChanneling() == false
		|| m_fNowTime >= m_fDuration)
	{
		SoundMgr::Stop(L"AS_Loop");
		Destroy(this);
		return;
	}

	if (m_pOwner)
	{
		m_tTransform.vPos = m_pOwner->GetPos();
		m_tTransform.vPos += m_vOffset;
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
		if (attInfo.fNowTime >= 0.23f)
		{
			attInfo.fNowTime = 0.f;
			attInfo.iHitCount %= 15;

			for (int i = 0; i < m_iPerHitCount; ++i)
			{
				HitInfo hitInfo = { 50000, attInfo.iHitCount, false };
				attInfo.pHitObj->Hit(hitInfo);
				attInfo.iHitCount++;
			}

			SoundMgr::Play(L"AS_Hit_SFX");
			Vec2 effectPos = attInfo.vecEffectPos[m_iMaxHitCount / m_iPerHitCount - 1] + Vec2(float(rand() % 30 - 60), float(rand() % 30 - 60));
			HitEffect* pEffect = Instantiate_NoInit<HitEffect>(eLayerType::LT_EFFECT);
			pEffect->SetPos(effectPos);
			pEffect->Set_EffectTex(m_pHitEffect);
			pEffect->SetSize(Vec2(552.f, 443.f));
			pEffect->Set_SpriteLength(14);
			pEffect->SetDuration(0.05f);
			pEffect->Initialize();
		}
		++it;
	}

	m_pAnimator->Update(); 
	m_pBottomAnimator->Update();
}

void AS_Obj::Render()
{
	m_pBottomAnimator->Render();
	m_pAnimator->Render();
	//m_pCollider->Render();
}

void AS_Obj::Release()
{
	delete m_pBottomAnimator;
}

void AS_Obj::Skill_Start()
{
	m_pAnimator->PlayAnimation(L"Asura");
	m_pBottomAnimator->PlayAnimation(L"Asura_Bottom");
	SoundMgr::Play(L"AS_Loop");
}

void AS_Obj::OnCollisionEnter(Collider* other)
{
	push_AttackInfo(other);
}

void AS_Obj::OnCollisionStay(Collider* other)
{
}

void AS_Obj::OnCollisionExit(Collider* other)
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
