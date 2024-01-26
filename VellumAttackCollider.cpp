#include "VellumAttackCollider.h"
#include "Player.h"


void VellumAttackCollider::Initialize()
{
	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetCollisionInactive();
}
void VellumAttackCollider::Render()
{
	if (m_pCollider->IsCollisionOn())
		m_pCollider->Render();
}

void VellumAttackCollider::OnCollisionEnter(Collider* other)
{
	HitInfo tHitInfo = { 20000, 1 };
	static_cast<Player*>(other->GetOwner())->Hit(tHitInfo);
}

void VellumAttackCollider::SetCollisionSize(const Vec2& _vSize)
{
	if (m_pCollider)
		m_pCollider->SetSize(_vSize);
}

void VellumAttackCollider::SetCollisionOffset(const Vec2& _vOffset)
{
	if (m_pCollider)
		m_pCollider->SetOffset(_vOffset);
}

void VellumAttackCollider::SetCollisionOnOff(const bool& _b)
{
	if (m_pCollider)
		m_pCollider->SetCollActive(_b);
}
