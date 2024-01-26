#include "Rigidbody.h"
#include "TimeMgr.h"
#include "GameObject.h"

Rigidbody::Rigidbody()
	: m_pOwner(nullptr)
	, m_bIsGround(false)
	, m_bUseGravity(true)
	, m_bActive(true)
	, m_fMass(1.0f)
	, m_fFriction(0.f)
	, m_vGravity{ 0.f, 200.f } 
	, m_vForce{}
	, m_vAccel{}
	, m_vVelocity{}
	, m_vLimitedVelocity{ 5000.f, 600.f }
{
	SetName(L"Rigidbody");
}

Rigidbody::~Rigidbody()
{
}


void Rigidbody::Update()
{
	if (!m_bActive)
		return;

	m_vAccel = m_vForce / m_fMass;

	m_vVelocity += m_vAccel;


	if (m_bUseGravity)
	{
		if (m_bIsGround)
		{
			Vec2 gravity = m_vGravity;
			gravity.normalize();

			float dot = Vec2::Dot(m_vVelocity, gravity);
			m_vVelocity -= gravity * dot;
		}
		else
		{
			m_vVelocity += m_vGravity * TimeMgr::DeltaTime();
		}

		Vec2 gravity = m_vGravity;
		gravity.normalize();
		float dot = Vec2::Dot(m_vVelocity, gravity);
		gravity = gravity * dot;

		Vec2 sideVelocity = m_vVelocity - gravity;
		if (m_vLimitedVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= m_vLimitedVelocity.y;
		}

		if (m_vLimitedVelocity.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= m_vLimitedVelocity.x;
		}
		m_vVelocity = gravity + sideVelocity;
	}
	

	Vec2 pos = m_pOwner->GetPos();
	pos += m_vVelocity * TimeMgr::DeltaTime();
	m_pOwner->SetPos(pos);

	m_vForce = Vec2::Zero;
}




