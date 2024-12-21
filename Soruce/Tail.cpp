#include "Tail.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "joObject.h"
#include "Vellum.h"

Tail::Tail()
	: m_pOwner(nullptr)
{
}

Tail::~Tail()
{
}

void Tail::Initialize()
{
	m_pCollider = new Collider;
	m_pCollider->SetCollisionInactive();
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize({ 280.f, 335.f });
	m_pCollider->SetOffset(Vec2(-20.f, 160.f));

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	JoTexture* m_pTailTex_L = ResourceMgr::Find<JoTexture>(L"Vellum_Tail_L");
	JoTexture* m_pTailTex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Tail_R");

	m_pAnimator->CreateAnimation(L"Tail_L", m_pTailTex_L, Vec2::Zero, Vec2(923.f, 717.f), Vec2::Zero, 41, 9, 0.09f);
	m_pAnimator->CreateAnimation(L"Tail_R", m_pTailTex_R, Vec2::Zero, Vec2(923.f, 717.f), Vec2::Zero, 41, 9, 0.09f);
	
	Events* pEvent_Tail_L = m_pAnimator->GetEvents(L"Tail_L");
	Events* pEvent_Tail_R = m_pAnimator->GetEvents(L"Tail_R");
	pEvent_Tail_L->frameEvents[24] = std::bind(&Collider::SetCollisionActive, m_pCollider);
	pEvent_Tail_L->frameEvents[32] = std::bind(&Collider::SetCollisionInactive, m_pCollider);
	pEvent_Tail_R->frameEvents[24] = std::bind(&Collider::SetCollisionActive, m_pCollider);
	pEvent_Tail_R->frameEvents[32] = std::bind(&Collider::SetCollisionInactive, m_pCollider);
}

void Tail::Update()
{
	m_pAnimator->Update();
	if (m_pAnimator->IsEndAnim())
		Destroy(this);
}

void Tail::Render()
{
	m_pAnimator->Render();
	/*if (m_pCollider->IsCollisionOn())
		m_pCollider->Render();*/
}

void Tail::Hit(const HitInfo& _hitInfo)
{
	// º§·ëÀÇ ÇÇ¸¦ ±ð´Â´Ù.
	//m_pOwner->AddHp(-_hitInfo.iDamage);
	DamageNum* pDNum = Instantiate<DamageNum>(eLayerType::LT_UI);
	pDNum->Init_Number(std::to_string(_hitInfo.iDamage));
	pDNum->SetCritical(_hitInfo.bCritical);

	Vec2 vRenderPos = GetPos();
	JoTexture* pDamageTex = pDNum->GetDamageTex();
	vRenderPos.y -= float(pDamageTex->GetHeight()) * 0.5f * _hitInfo.iHitCount;

	pDNum->SetPos(vRenderPos);
}

void Tail::OnCollisionEnter(Collider* _pOther)
{
	HitInfo hitInfo = { 9999999, 1 };
	
	Player* pPlayer = dynamic_cast<Player*>(_pOther->GetOwner());
	if (pPlayer)
		pPlayer->Hit(hitInfo);
}

void Tail::PlayAnim(const bool& _bRight)
{
	if (_bRight)
		m_pAnimator->PlayAnimation(L"Tail_R", false);
	else
		m_pAnimator->PlayAnimation(L"Tail_L", false);
}
