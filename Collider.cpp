#include "Collider.h"
#include "GameObject.h"
#include "RenderMgr.h"
#include "MainCamera.h"


UINT32 Collider::s_CollisionID = 0;

Collider::Collider()
	: m_iID(s_CollisionID++)
	, m_vSize{}
	, m_renderColor(RGB(0, 255, 0))
	, m_bActiveColl(true)
	, m_pOwner(nullptr)
{
	SetName(L"Collider");
}

Collider::~Collider()
{
}

void Collider::Initialize()
{
}

void Collider::Update()
{
}

void Collider::LateUpdate()
{
}
void Collider::Render()
{
	Vec2 pos = GetOwner()->GetPos();
	pos += GetOffset();
	pos = camera::pMainCamera->CalcRenderPos(pos);

	Vec2 vLeftTop = {};
	vLeftTop.x = pos.x - GetSize().x * 0.5f;
	vLeftTop.y = pos.y - GetSize().y * 0.5f;

	Vec2 vRightBottom = {};
	vRightBottom.x = pos.x + GetSize().x * 0.5f;
	vRightBottom.y = pos.y + GetSize().y * 0.5f;

	RenderMgr::RenderRectangle(
		  vLeftTop.x
		, vLeftTop.y
		, vRightBottom.x
		, vRightBottom.y
		, RGB(0, 255, 0), 1.0f);
}

void Collider::OnCollisionEnter(Collider* other)
{
	m_renderColor = RGB(255, 0, 0);
	other->GetOwner()->OnCollisionEnter(this);
}

void Collider::OnCollisionStay(Collider* other)
{
	other->GetOwner()->OnCollisionStay(this);
}

void Collider::OnCollisionExit(Collider* other)
{
	m_renderColor = RGB(0, 255, 0);
	other->GetOwner()->OnCollisionExit(this);
}
