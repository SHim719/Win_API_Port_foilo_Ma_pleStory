#include "Scene_Rutabyss.h"
#include "Camera.h"
#include "BackGround.h"
#include "GiantRootBG.h"
#include "ResourceMgr.h"
#include "SoundMgr.h"
#include "Player.h"
#include "Girl.h"
#include "ShopBoy.h"
#include "UIMgr.h"
#include "Portal.h"


Scene_Rutabyss::Scene_Rutabyss()
{
}

Scene_Rutabyss::~Scene_Rutabyss()
{
}

void Scene_Rutabyss::Initialize()
{
	m_vLimitPosX.x = 233.f;
	m_vLimitPosX.y = 2283.f;

	GiantRootBG* pBg = Instantiate<GiantRootBG>(eLayerType::LT_BACKGROUND);
	JoTexture* bgTex = ResourceMgr::Find<JoTexture>(L"BG_GiantRoot1");
	
	float texWidth = (float)bgTex->GetWidth();
	float texHeight = (float)bgTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight, Vec2::Zero);

	m_pixelDC = ResourceMgr::Find<JoBmp>(L"GiantRoot_Pixel")->Get_BmpDC();

	Girl* pGirl = Instantiate<Girl>(eLayerType::LT_NPC);
	ShopBoy* pShopBoy = Instantiate<ShopBoy>(eLayerType::LT_NPC);

	/*Portal* pPortal1 = Instantiate<Portal>(eLayerType::LT_OBJECT);
	pPortal1->SetPos(Vec2(1980.f, 830.f));
	pPortal1->Set_MovePos({ 86.f, 687.f });
	pPortal1->Set_SceneName(L"Scene_Boss");*/


	Portal* pPortal2 = Instantiate<Portal>(eLayerType::LT_OBJECT);
	pPortal2->SetPos(Vec2(500.f, 830.f));
	pPortal2->Set_MovePos( {120.f, 840.f });
	pPortal2->Set_SceneName(L"Scene_Grandis");

	/*Portal* pPortal3 = Instantiate<Portal>(eLayerType::LT_OBJECT);
	Portal* pPortal4 = Instantiate<Portal>(eLayerType::LT_OBJECT);*/
}


void Scene_Rutabyss::OnEnter()
{
	SoundMgr::Play(L"GiantRoot");

	Camera::SetMinCameraPos(m_vMinCameraPos);
	Camera::SetMaxCameraPos(m_vMaxCameraPos);

	AddObj(s_pMainPlayer, eLayerType::LT_PLAYER);
	Camera::SetTarget(s_pMainPlayer);
	s_pMainPlayer->SetLimitPosX(m_vLimitPosX);
	s_pMainPlayer->SetPixelDC(m_pixelDC);

	UIMgr::SetCanUseUI(true);
}

void Scene_Rutabyss::OnExit()
{
	SoundMgr::Stop(L"GiantRoot");
	GetLayer(eLayerType::LT_PLAYER)->Release();
}
