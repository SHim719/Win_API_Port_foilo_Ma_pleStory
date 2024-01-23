#include "Vellum.h"
#include "ResourceMgr.h"
#include "joObject.h"

Vellum::Vellum()
{
}

Vellum::~Vellum()
{
}

void Vellum::Initialize()
{
	m_iHp = 5000000;

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(140.f, 600.f));

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	JoTexture* m_pIdleTex_L = ResourceMgr::Find<JoTexture>(L"Vellum_Idle_L");
	JoTexture* m_pIdleTex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Idle_R");

	m_pAnimator->CreateAnimation(L"Vellum_Idle_L", m_pIdleTex_L, Vec2(0.0f, 0.0f), Vec2(900.f, 800.f), Vec2::Zero, 23, 8, 0.15f);
	m_pAnimator->CreateAnimation(L"Vellum_Idle_R", m_pIdleTex_R, Vec2(0.0f, 0.0f), Vec2(900.f, 800.f), Vec2::Zero, 23, 8, 0.15f);

	m_pAnimator->PlayAnimation(L"Vellum_Idle_L");
}

void Vellum::Update()
{
	m_pAnimator->Update();
}

void Vellum::LateUpdate()
{
}

void Vellum::Render()
{
	m_pAnimator->Render();
	m_pCollider->Render();
}

void Vellum::Hit(const HitInfo& _hitInfo)
{
	DamageNum* pDNum = Instantiate<DamageNum>(eLayerType::LT_UI);
	pDNum->Init_Number(std::to_string(_hitInfo.iDamage));
	pDNum->SetCritical(_hitInfo.bCritical);

	Vec2 vDamagePos = GetPos();
	JoTexture* pDamageTex = pDNum->GetDamageTex();
	vDamagePos.x -= 250.f;
	vDamagePos.y -= float(pDamageTex->GetHeight()) * 0.5f * _hitInfo.iHitCount;

	pDNum->SetPos(vDamagePos);
	
}
