#include "Eagle.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "EG_GameMgr.h"

EG_GameMgr* Eagle::s_pGameMgr = nullptr;

void Eagle::Initialize()
{
	m_pEagleTex = ResourceMgr::Find<JoTexture>(L"Eagle");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Fly_L", m_pEagleTex, Vec2(0.f, 250.f), Vec2(119.f, 103.f), Vec2::Zero, 6, 0.2f);
	m_pAnimator->CreateAnimation(L"Fly_R", m_pEagleTex, Vec2(119.f * 6.f, 250.f), Vec2(119.f, 103.f), Vec2::Zero, 6, 0.2f);
	m_pAnimator->CreateAnimation(L"Die_L", m_pEagleTex, Vec2(0.f, 0.f), Vec2(179.f, 125.f), Vec2::Zero, 10, 0.2f);
	m_pAnimator->CreateAnimation(L"Die_R", m_pEagleTex, Vec2(0.f, 125.f), Vec2(179.f, 125.f), Vec2::Zero, 10, 0.2f);

	m_pAnimator->GetEvents(L"Die_L")->frameEvents[9] = bind(&GameObject::SetDeath, this);
	m_pAnimator->GetEvents(L"Die_R")->frameEvents[9] = bind(&GameObject::SetDeath, this);

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize({ 110.f, 100.f });

	m_pRigidbody = new Rigidbody;
	m_pRigidbody->SetOwner(this);
	m_pRigidbody->SetUseGravity(false);

	//Set_RandomPos();
	SetPos({ 512.f, 768.f * 0.5f });
	Reset_Dir();
}

void Eagle::Update()
{
	static float fNowTime = 0.f;
	fNowTime += TimeMgr::DeltaTime();

	if (fNowTime >= m_fMoveTime)
	{
		fNowTime = 0.f;
		Reset_Dir();
	}

	m_pRigidbody->Update();
	Check_Area();
	m_pAnimator->Update();
}

void Eagle::Render()
{
	m_pAnimator->Render();
	m_pCollider->Render();
}

void Eagle::Hit(const HitInfo& _hitInfo)
{
	m_bDie = true;
	m_pCollider->SetCollisionInactive();
	m_pRigidbody->SetVelocity(Vec2::Zero);
	if (m_vDir.x > 0.f)
		m_pAnimator->PlayAnimation(L"Die_R", false);
	else
		m_pAnimator->PlayAnimation(L"Die_L", false);

	s_pGameMgr->Minus_EagleCnt();
}

void Eagle::Reset_Dir()
{
	if (m_bDie)
		return;
	float fTheta = float(rand() % 360);
	float fRadian = fTheta * 3.141592f / 180.f;

	m_vDir = Vec2(cosf(fRadian), sinf(fRadian));

	m_pRigidbody->SetVelocity(m_vDir * m_fSpeed);
	if (m_vDir.x > 0.f)
		m_pAnimator->PlayAnimation(L"Fly_R");
	else
		m_pAnimator->PlayAnimation(L"Fly_L");

	m_fMoveTime = float(rand() % 3 + 1);
}

void Eagle::Check_Area()
{
	Vec2 vPos = GetPos();

	if (vPos.x <= 200.f)
	{
		vPos.x = 201.f;
		Reset_Dir();
	}
	else if (vPos.x >= 800.f)
	{
		vPos.x = 799.f;
		Reset_Dir();
	}
	else if (vPos.y <= 200.f)
	{
		vPos.y = 201.f;
		Reset_Dir();
	}
	else if (vPos.y >= 568.f)
	{
		vPos.y = 567.f;
		Reset_Dir();
	}
	
	SetPos(vPos);
}
