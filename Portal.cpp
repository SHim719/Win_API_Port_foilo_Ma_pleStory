#include "Portal.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"

Portal::Portal()
	: m_vMovePos{}
	, m_pPortalTex(nullptr)
	, m_wsSceneName(L"")
{
}

Portal::~Portal()
{
}

void Portal::Initialize()
{
	m_pPortalTex = ResourceMgr::Find<JoTexture>(L"Portal");

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize({ 94.f, 122.f });

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Portal", m_pPortalTex, Vec2(0.f, 0.f), Vec2(104.f, 142.f), Vec2::Zero,
		8, 0.2f);

	m_pAnimator->PlayAnimation(L"Portal", true);

}

void Portal::Update()
{
	m_pAnimator->Update();
}

void Portal::Render()
{
	m_pAnimator->Render();
	m_pCollider->Render();
}

void Portal::OnCollisionStay(Collider* other)
{
	if (KeyMgr::GetKeyDown(eKeyCode::Up))
	{
		MoveTo(other->GetOwner());
	}
		
}

void Portal::MoveTo(GameObject* _pObj)
{
	SoundMgr::Play(L"Portal_SFX");
	SceneMgr::Reservation_ChangeScene(m_wsSceneName, m_vMovePos);
}
