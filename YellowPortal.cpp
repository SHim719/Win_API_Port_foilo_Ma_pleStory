#include "YellowPortal.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"

YellowPortal::YellowPortal()
	: m_vMovePos{}
	, m_pPortalTex(nullptr)
{
}

YellowPortal::~YellowPortal()
{
}

void YellowPortal::Initialize()
{
	m_pPortalTex = ResourceMgr::Find<JoTexture>(L"YellowPortal");

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize({ 94.f, 122.f });

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"YellowPortal", m_pPortalTex, Vec2(0.f, 0.f), Vec2(94.f, 133.f), Vec2::Zero,
		14, 0.2f);

	m_pAnimator->PlayAnimation(L"YellowPortal", true);
}

void YellowPortal::Update()
{
	m_pAnimator->Update();
}

void YellowPortal::Render()
{
	m_pAnimator->Render();
	m_pCollider->Render();
}

void YellowPortal::OnCollisionStay(Collider* other)
{
	if (KeyMgr::GetKeyDown(eKeyCode::Up))
	{
		MoveTo(other->GetOwner());
	}
}

void YellowPortal::MoveTo(GameObject* _pObj)
{
	SoundMgr::Play(L"Portal_SFX");
	_pObj->SetPos(m_vMovePos);
}
