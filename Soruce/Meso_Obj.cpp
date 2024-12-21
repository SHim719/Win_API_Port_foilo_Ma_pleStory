#include "Meso_Obj.h"
#include "RenderMgr.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Inventory.h"
#include "joObject.h"
#include "RenderMgr.h"
#include "Camera.h"
#include "SoundMgr.h"
#include "TimeMgr.h"


JoTexture* Meso_Obj::m_pMesoTex = nullptr;

void Meso_Obj::Initialize()
{
	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize({ 32.f, 32.f });

	m_pRigidbody = new Rigidbody;
	m_pRigidbody->SetOwner(this);
	m_pRigidbody->SetVelocity({ 0.f, -300.f });
	m_pRigidbody->SetGravity(Vec2(0.f, 500.f));

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);
	m_pAnimator->CreateAnimation(L"Meso", m_pMesoTex, Vec2::Zero, { 32.f, 32.f }, Vec2::Zero, 4, 0.25f);
	m_pAnimator->PlayAnimation(L"Meso");
}

void Meso_Obj::Render()
{
	m_pAnimator->GetActiveAnim()->SetAlpha(m_fAlpha);
	m_pAnimator->Render();
}

void Meso_Obj::OnCollisionStay(Collider* _pOther)
{
	if (m_eState == State::Obtain)
		return;

	if (KeyMgr::GetKeyDown(eKeyCode::Z))
	{
		Player* _pPlayer = static_cast<Player*>(_pOther->GetOwner());
		_pPlayer->GetInventory()->Add_Meso(5000);
		SoundMgr::Play(L"Obtain_SFX");
		m_pRigidbody->SetUseGravity(true);
		m_pRigidbody->SetVelocityY(-200.f);
		m_fNowTime = 0.f;
		m_eState = State::Obtain;
		m_fAlpha = 0.7f;
	}
}
