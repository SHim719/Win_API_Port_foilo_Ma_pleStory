#include "AttackCollider.h"
#include "Player.h"

void AttackCollider::Initialize()
{
	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetCollisionInactive();

	m_bCanHit = false;
}

void AttackCollider::Update()
{
	if (m_pOwner)
	{
		m_tTransform.vPos = m_pOwner->GetPos();
	}

}

void AttackCollider::Render()
{
	//if (m_pCollider->IsCollisionOn())
		//m_pCollider->Render();
}

void AttackCollider::OnCollisionEnter(Collider* other)
{
	//HitInfo tHitInfo = { 20000, 1 };
	//static_cast<Player*>(other->GetOwner())->Hit(tHitInfo);

	m_pOwner->SetState_Attack();
}

void AttackCollider::OnCollisionStay(Collider* _pOther)
{
	m_pOwner->SetState_Attack();
	if (m_bCanHit)
	{
		HitInfo tHitInfo = { 1000, 1 };
		static_cast<Player*>(_pOther->GetOwner())->Hit(tHitInfo);
		m_bCanHit = false;
	}	
}

void AttackCollider::SetCollisionSize(const Vec2& _vSize)
{
	if (m_pCollider)
		m_pCollider->SetSize(_vSize);
}

void AttackCollider::SetCollisionOffset(const Vec2& _vOffset)
{
	if (m_pCollider)
		m_pCollider->SetOffset(_vOffset);
}

void AttackCollider::SetCollisionOnOff(const bool& _b)
{
	if (m_pCollider)
		m_pCollider->SetCollActive(_b);
}
