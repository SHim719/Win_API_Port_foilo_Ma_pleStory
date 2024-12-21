#include "LevelUp.h"
#include "ResourceMgr.h"
#include "SoundMgr.h"
#include "joObject.h"
#include "Enemy.h"


void LevelUp::Initialize()
{
	m_pLevelUpTex = ResourceMgr::Find<JoTexture>(L"LevelUp");

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize({ 904.f, 904.f });
	m_pCollider->SetCollisionInactive();

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"LevelUp", m_pLevelUpTex,
		Vec2::Zero, Vec2(904.f, 904.f), Vec2::Zero, 21, 4, 0.15f);

	m_pAnimator->PlayAnimation(L"LevelUp", false);
	SoundMgr::Play(L"LevelUp_SFX");
}

void LevelUp::Update()
{
	Vec2 vPos = m_pOwner->GetPos();
	SetPos(vPos + Vec2(0.f, -200.f));
	if (m_pAnimator->GetNowFrame() == 16)
		m_pCollider->SetCollisionActive();
	else if (m_pAnimator->GetNowFrame() == 17)
		m_pCollider->SetCollisionInactive();
	else if (m_pAnimator->IsEndAnim())
		Destroy(this);

	m_pAnimator->Update();
}

void LevelUp::Render()
{
	m_pAnimator->Render();
}

void LevelUp::OnCollisionEnter(Collider* _pOther)
{
	HitInfo _info = { 99999999, 1, true };
	static_cast<Enemy*>(_pOther->GetOwner())->Hit(_info);
}
