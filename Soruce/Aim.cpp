#include "Aim.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "RenderMgr.h"
#include "Enemy.h"
#include "SoundMgr.h"
#include "EG_GameMgr.h"
#include "Camera.h"



void Aim::Initialize()
{
	m_pCursorTex = ResourceMgr::Find<JoTexture>(L"Aim");

	m_pCollider = new Collider;
	m_pCollider->SetOwner(this);
	m_pCollider->SetSize(Vec2(1.f, 1.f));
}

void Aim::Update()
{
	Vec2 vMousePos = KeyMgr::GetMousePos();
	SetPos(vMousePos);

	m_bHit = false;
}

void Aim::Render()
{
	Vec2 vPos = GetPos();
	RenderMgr::RenderImage(m_pCursorTex
		, vPos.x - m_pCursorTex->GetWidth() * 0.5f, vPos.y - m_pCursorTex->GetHeight() * 0.5f
		, vPos.x + m_pCursorTex->GetWidth() * 0.5f, vPos.y + m_pCursorTex->GetHeight() * 0.5f);

	m_pCollider->Render();
}

void Aim::OnCollisionStay(Collider* _pOther)
{
	if (m_bHit
		|| m_pGameMgr->IsGameEnd())
		return;

	if (KeyMgr::GetKeyDown(eKeyCode::LButton))
	{
		Camera::Set_Shaking(0.1f, 3.f);
		SoundMgr::Play(L"Aim_Shot");
		m_bHit = true;
		HitInfo info = {};
		static_cast<Enemy*>(_pOther->GetOwner())->Hit(info);
	}
}


