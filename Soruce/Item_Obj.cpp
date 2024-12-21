#include "Item_Obj.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Inventory.h"
#include "joObject.h"
#include "RenderMgr.h"
#include "Camera.h"
#include "SoundMgr.h"
#include "TimeMgr.h"


HDC Item_Obj::m_Pixel = nullptr;

Item_Obj::Item_Obj()
	: m_pItem(nullptr)
	, m_iCount(0)
{
}

Item_Obj::~Item_Obj()
{

}

void Item_Obj::Initialize()
{
	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize({ 32.f, 32.f });

	m_pRigidbody = new Rigidbody;
	m_pRigidbody->SetOwner(this);
	m_pRigidbody->SetVelocity({ 0.f, -300.f });
	m_pRigidbody->SetGravity(Vec2(0.f, 500.f));
}

void Item_Obj::Update()
{

	switch (m_eState)
	{
	case Item_Obj::State::Appear:
		Appear();
		break;
	case Item_Obj::State::Loop:
		Loop();
		break;
	case Item_Obj::State::Obtain:
		Obtain();
		break;
	}
	
	m_pRigidbody->Update();
}

void Item_Obj::Render()
{
	Vec2 vRenderPos = GetPos();
	vRenderPos = Camera::CalcRenderPos(vRenderPos);
	RenderMgr::RenderImage(m_pItem->GetItemTex()
		, vRenderPos.x - 16.f, vRenderPos.y - 16.f
		, vRenderPos.x + 16.f, vRenderPos.y + 16.f,
		m_fAlpha);
}

void Item_Obj::CheckGround()
{
	if (RGB(255, 0, 255) == GetPixel(m_Pixel, (int)GetPos().x, int(GetPos().y + 16.f + 1.f)))
	{
		m_eState = State::Loop;
		m_pRigidbody->SetUseGravity(false);
		m_pRigidbody->SetVelocityY(-m_fSpeed);
		while ((RGB(255, 0, 255) == GetPixel(m_Pixel, (int)GetPos().x, int(GetPos().y + 16.f)))) 
			m_tTransform.vPos.y -= 1.f;	
	}

}

void Item_Obj::OnCollisionStay(Collider* _pOther)
{
	if (m_eState == State::Obtain)
		return;

	if (KeyMgr::GetKeyDown(eKeyCode::Z))
	{
		Player* _pPlayer = static_cast<Player*>(_pOther->GetOwner());
		_pPlayer->GetInventory()->Insert_Item(m_pItem, m_iCount);
		SoundMgr::Play(L"Obtain_SFX");
		m_pRigidbody->SetUseGravity(true);
		m_pRigidbody->SetVelocityY(-200.f);
		m_fNowTime = 0.f;
		m_eState = State::Obtain;
		m_fAlpha = 0.7f;
	}
	
}

void Item_Obj::Appear()
{
	CheckGround();
}

void Item_Obj::Loop()
{
	m_fNowTime += TimeMgr::DeltaTime();
	if (m_fNowTime >= 1.f)
	{
		m_fNowTime = 0.f;
		m_pRigidbody->SetVelocityY(-m_pRigidbody->GetVelocity().y);
	}
}

void Item_Obj::Obtain()
{
	m_fNowTime += TimeMgr::DeltaTime();
	if (m_fNowTime >= 0.8f)
		Destroy(this);
}
