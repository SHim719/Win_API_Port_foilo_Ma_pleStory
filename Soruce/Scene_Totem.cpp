#include "Scene_Totem.h"
#include "CollisionMgr.h"
#include "joObject.h"
#include "MainGame.h"
#include "Camera.h"
#include "Player.h"
#include "BackGround.h"
#include "ResourceMgr.h"
#include "TotemBar.h"
#include "TS_GameMgr.h"
#include "Totem_Player.h"
#include "TimerUI.h"
#include "SoundMgr.h"
#include "UIMgr.h"
#include "TimeMgr.h"

Scene_Totem::Scene_Totem()
{
}

Scene_Totem::~Scene_Totem()
{
}

void Scene_Totem::OnGameStart()
{
	JoTexture* pBGTex = ResourceMgr::Find<JoTexture>(L"BG_Totem");
	BackGround* pBG = Instantiate<BackGround>(eLayerType::LT_BACKGROUND);
	pBG->SetBgTex(pBGTex);

	TimerUI* pTimerUI = Instantiate<TimerUI>(eLayerType::LT_UI);
	pTimerUI->SetTime(30.f);

	TS_GameMgr* pMgr = Instantiate<TS_GameMgr>(eLayerType::LT_NONE);
	pMgr->SetTimerUI(pTimerUI);

	Totem_Player* pPlayer = Instantiate<Totem_Player>(eLayerType::LT_OBJECT);
	pPlayer->SetPos({ 427.f,  565.f });
	pPlayer->Set_Manager(pMgr);
	pPlayer->Set_TotemBar(Instantiate<TotemBar>(eLayerType::LT_UI));

	TimeMgr::SetTimeScale(0.f);
}

void Scene_Totem::OnEnter()
{
	OnGameStart();
	Camera::Set_NoLimit(true);
	Camera::SetTarget(nullptr);
	Camera::SetLookAt(Vec2(1364.f * 0.5f, 768.f * 0.5f));
	UIMgr::SetCanUseUI(false);
	SoundMgr::Play(L"TotemBGM");
}

void Scene_Totem::OnExit()
{
	TimeMgr::SetTimeScale(1.f);
	Camera::SetTarget(s_pMainPlayer);
	Camera::Set_NoLimit(false);
	UIMgr::SetCanUseUI(true);
	Scene::Release();
	SoundMgr::Stop(L"TotemBGM");
}
