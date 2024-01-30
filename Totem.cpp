#include "Totem.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "Camera.h"
#include "joObject.h"

Totem::Totem()
{
}

Totem::~Totem()
{
}

void Totem::Initialize()
{
	int iRand = rand() % 3;
	switch (iRand)
	{
	case 0:
		m_pTotemTex = ResourceMgr::Find<JoTexture>(L"뱀토템");
		break;
	case 1:
		m_pTotemTex = ResourceMgr::Find<JoTexture>(L"범토템");
		break;
	case 2:
		m_pTotemTex = ResourceMgr::Find<JoTexture>(L"원숭이토템");
		break;
	}

	m_pRigidbody = new Rigidbody;
	m_pRigidbody->SetOwner(this);
	m_pRigidbody->SetUseGravity(false);
	m_pRigidbody->SetGravity(Vec2(0.f, 1000.f));
}

void Totem::Update()
{
	m_pRigidbody->Update();
	
	if (GetPos().y > 1200.f)
		Destroy(this);
}

void Totem::Render()
{
	Vec2 vRenderPos = GetPos();
	vRenderPos = Camera::CalcRenderPos(vRenderPos);

	RenderMgr::RenderImage(m_pTotemTex
		, vRenderPos.x - m_pTotemTex->GetWidth() * 0.5f
		, vRenderPos.y - m_pTotemTex->GetHeight() * 0.5f
		, vRenderPos.x + m_pTotemTex->GetWidth() * 0.5f
		, vRenderPos.y + m_pTotemTex->GetHeight() * 0.5f);
}
