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

Scene_Totem::Scene_Totem()
{
}

Scene_Totem::~Scene_Totem()
{
}

void Scene_Totem::Initialize()
{
	JoTexture* pBGTex = ResourceMgr::Find<JoTexture>(L"BG_Totem");
	BackGround* pBG = Instantiate<BackGround>(eLayerType::LT_BACKGROUND);
	pBG->SetBgTex(pBGTex);

	Instantiate<TotemBar>(eLayerType::LT_UI);

	TS_GameMgr* pMgr = Instantiate<TS_GameMgr>(eLayerType::LT_NONE);
}

void Scene_Totem::OnEnter()
{
	Camera::Set_NoLimit(true);
	Camera::SetTarget(nullptr);
	Camera::SetLookAt(Vec2(1364.f * 0.5f, 768.f * 0.5f));
}

void Scene_Totem::OnExit()
{
	Camera::SetTarget(s_pMainPlayer);
	Camera::Set_NoLimit(false);
}
