#include "VellumStone.h"
#include "ResourceMgr.h"
#include "joObject.h"
#include "Player.h"

VellumStone::VellumStone()
{
}

VellumStone::~VellumStone()
{
}

void VellumStone::Initialize()
{
	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize({ 60.f, 270.f });
	m_pCollider->SetCollisionInactive();

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	
	JoTexture* pStoneTex = ResourceMgr::Find<JoTexture>(L"Vellum_Stone");
	JoTexture* pStoneEndTex = ResourceMgr::Find<JoTexture>(L"Vellum_Stone_End");

	function<void()> playeStoneEnd = [&]()-> void {m_pAnimator->PlayAnimation(L"Stone_End", false);};
	function<void()> SetCollisionOn = [&]()-> void 
		{
			m_pCollider->SetCollisionActive();
			m_pCollider->SetOffset(Vec2(10.f, 825.f));
		};
	function<void()> SetCollisionOff = [&]()-> void { m_pCollider->SetCollisionInactive(); };
	
	m_pAnimator->CreateAnimation(L"Stone", pStoneTex, Vec2::Zero, Vec2(247.f, 1937.f), Vec2::Zero, 23, 0.1f);
	m_pAnimator->CreateAnimation(L"Stone_End", pStoneEndTex, Vec2::Zero, Vec2(306.f, 276.f), Vec2(0.f, 820.f), 3, 0.3f);

	Events* pEvent_Stone = m_pAnimator->GetEvents(L"Stone");
	pEvent_Stone->frameEvents[22] = SetCollisionOn;
	pEvent_Stone->EndEvent = playeStoneEnd;

	Events* pEvent_Stone_End = m_pAnimator->GetEvents(L"Stone_End");
	pEvent_Stone_End->frameEvents[1] = SetCollisionOff;
	pEvent_Stone_End->EndEvent = [&]()-> void { SetActive(false); };	
}

void VellumStone::Update()
{
	m_pAnimator->Update();
}

void VellumStone::Render()
{
	m_pAnimator->Render();
	//m_pCollider->Render();
}

void VellumStone::OnCollisionEnter(Collider* _pOther)
{
	static_cast<Player*>(_pOther->GetOwner())->SetState_Stun();
}

void VellumStone::Play_Anim() const
{
	m_pAnimator->PlayAnimation(L"Stone", false);
}

