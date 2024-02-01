#include "DeepBreath.h"
#include "ResourceMgr.h"
#include "Player.h"

DeepBreath::DeepBreath()
{
}

DeepBreath::~DeepBreath()
{
}

void DeepBreath::Initialize()
{
	SetActive(false);

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize({ 341.f, 810.f });

	JoTexture* pBreathTex = ResourceMgr::Find<JoTexture>(L"Vellum_Breath_L");
	JoTexture* pBreathTex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Breath_R");
	JoTexture* pBreathEndTex = ResourceMgr::Find<JoTexture>(L"Vellum_Breath_End_L");
	JoTexture* pBreathEndTex_R = ResourceMgr::Find<JoTexture>(L"Vellum_Breath_End_R");

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Breath_L", pBreathTex, Vec2::Zero, Vec2(341.f, 810.f), Vec2::Zero, 6, 0.1f);
	m_pAnimator->CreateAnimation(L"Breath_End_L", pBreathEndTex, Vec2::Zero, Vec2(341.f, 679.f), Vec2(0.f, 43.f), 7, 0.1f);
	m_pAnimator->CreateAnimation(L"Breath_R", pBreathTex_R, Vec2::Zero, Vec2(341.f, 810.f), Vec2::Zero, 6, 0.1f);
	m_pAnimator->CreateAnimation(L"Breath_End_R", pBreathEndTex_R, Vec2::Zero, Vec2(341.f, 679.f), Vec2(0.f, 43.f), 7, 0.1f);

	function<void()> setInActive = [&]() ->void { SetActive(false); };

	Events* pEvent_Breath_End_L = m_pAnimator->GetEvents(L"Breath_End_L");
	pEvent_Breath_End_L->EndEvent = setInActive;
	Events* pEvent_Breath_End_R = m_pAnimator->GetEvents(L"Breath_End_R");
	pEvent_Breath_End_R->EndEvent = setInActive;
}

void DeepBreath::Update()
{
	m_pAnimator->Update();
}

void DeepBreath::Render()
{
	m_pAnimator->Render();
	//m_pCollider->Render();
}

void DeepBreath::OnCollisionEnter(Collider* _pOther)
{
	HitInfo hitInfo = { 9999999, 1 };
	static_cast<Player*>(_pOther->GetOwner())->Hit(hitInfo);
}

void DeepBreath::Play_BreathAnim(const bool& _bRight)
{
	if (_bRight)
		m_pAnimator->PlayAnimation(L"Breath_R");
	else
		m_pAnimator->PlayAnimation(L"Breath_L");

	if (m_pCollider)
		m_pCollider->SetCollisionActive();
	
}

void DeepBreath::Play_EndAnim(const bool& _bRight)
{
	if (_bRight)
		m_pAnimator->PlayAnimation(L"Breath_End_R", false);
	else
		m_pAnimator->PlayAnimation(L"Breath_End_L", false);

	if (m_pCollider)
		m_pCollider->SetCollisionInactive();
}

