#include "Scene_Eagle.h"
#include "CollisionMgr.h"
#include "joObject.h"
#include "Eagle.h"
#include "MainGame.h"
#include "Camera.h"
#include "Player.h"
#include "BackGround.h"
#include "ResourceMgr.h"
#include "Aim.h"
#include "BaldEagle.h"
#include "TimerUI.h"
#include "TimeMgr.h"
#include "EG_GameMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"

extern MainGame g_MainGame;

Scene_Eagle::Scene_Eagle()
{
}

Scene_Eagle::~Scene_Eagle()
{
}

void Scene_Eagle::GameStart()
{
	JoTexture* pBGTex = ResourceMgr::Find<JoTexture>(L"BG_Eagle");
	BackGround* pBG = Instantiate<BackGround>(eLayerType::LT_BACKGROUND);
	pBG->SetBgTex(pBGTex);

	for (int i = 0; i < 10; ++i)
	{
		Instantiate<BaldEagle>(eLayerType::LT_MONSTER);
		Instantiate<Eagle>(eLayerType::LT_MONSTER);
	}

	TimerUI* pTimerUI = Instantiate<TimerUI>(eLayerType::LT_UI);
	pTimerUI->SetPos({ 406.f, 25.f });
	pTimerUI->SetTime(20.f);

	EG_GameMgr* pGameMgr = Instantiate<EG_GameMgr>(eLayerType::LT_OBJECT);
	pGameMgr->SetTimerUI(pTimerUI);

	Eagle::Set_GameMgr(pGameMgr);

	Instantiate<Aim>(eLayerType::LT_UI)->Set_GameMgr(pGameMgr);
}

void Scene_Eagle::OnEnter()
{
	Camera::Set_NoLimit(true);
	Camera::SetTarget(nullptr);
	Camera::SetLookAt(Vec2(1024.f * 0.5f, 768.f * 0.5f));
	UIMgr::SetCanUseUI(false);

	CollisionMgr::SetCollisionEnabled(eLayerType::LT_MONSTER, eLayerType::LT_UI, true);
	TimeMgr::SetTimeScale(0.f);

	GameStart();
	g_MainGame.SetCursorRender(false);
}

void Scene_Eagle::OnExit()
{
	CollisionMgr::SetCollisionEnabled(eLayerType::LT_MONSTER, eLayerType::LT_UI, false);
	g_MainGame.SetCursorRender(true);
	Camera::SetTarget(s_pMainPlayer);
	Camera::Set_NoLimit(false);
	TimeMgr::SetTimeScale(1.f);
	UIMgr::SetCanUseUI(true);

	Scene::Release();
	SoundMgr::Stop(L"Nautilus");
}
