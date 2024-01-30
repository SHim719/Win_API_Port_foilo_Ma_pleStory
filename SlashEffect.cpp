#include "SlashEffect.h"
#include "ResourceMgr.h"
#include "SoundMgr.h"
#include "TS_GameMgr.h"
#include "joObject.h"


void SlashEffect::Initialize(const int& _iNum, const Vec2& _vSize, const Vec2& _vOffset, const UINT& _iLength)
{
	wstring wsName = to_wstring(_iNum) + L"∞›¿Ã∆Â∆Æ";
	JoTexture* pSlashTex = ResourceMgr::Find<JoTexture>(wsName);

	m_pAnimator = new Animator;
	m_pAnimator->SetOwner(this);

	m_pAnimator->CreateAnimation(L"Slash", pSlashTex, Vec2::Zero, _vSize, _vOffset, _iLength, 0.07f, true);
	m_pAnimator->GetEvents(L"Slash")->EndEvent = bind(&SlashEffect::End_Anim, this);
	m_pAnimator->PlayAnimation(L"Slash", false);

	wsName = L"Slash" + to_wstring(_iNum);
	SoundMgr::Play(wsName);
}

void SlashEffect::Update()
{
	m_pAnimator->Update();
}

void SlashEffect::Render()
{
	m_pAnimator->Render();
}

void SlashEffect::End_Anim()
{
	m_pGameMgr->Kill_Totem();
	Destroy(this);
}
