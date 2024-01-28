#include "Scene_Grandis.h"
#include "ResourceMgr.h"
#include "ChewBG.h"
#include "joObject.h"
#include "SoundMgr.h"
#include "Player.h"
#include "Camera.h"
#include "RapidStream.h"
#include "RhyTurtle.h"
#include "CT_RhyTurtle.h"
#include "animTest.h"

Scene_Grandis::Scene_Grandis()
{
}

Scene_Grandis::~Scene_Grandis()
{
}

void Scene_Grandis::Initialize()
{
	/*120.0f;
	840.f;*/

	m_vLimitPosX.x = 0.f;
	m_vLimitPosX.y = 5675.f;

	ChewBG* pBg = Instantiate<ChewBG>(eLayerType::LT_BACKGROUND);
	JoTexture* bgTex = ResourceMgr::Find<JoTexture>(L"BG_Chew1");

	float texWidth = (float)bgTex->GetWidth();
	float texHeight = (float)bgTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight, Vec2::Zero);

	m_vMaxCameraPos.y -= 100.f;

	m_pixelDC = ResourceMgr::Find<JoBmp>(L"Chew_Pixel")->Get_BmpDC();

	RapidStream* pStream = Instantiate<RapidStream>(eLayerType::LT_OBJECT);

	

	Init_Monster();

	/*animtest* test = Instantiate<animtest>(eLayerType::LT_MONSTER);
	test->SetPos({ 140.f, 840.f });*/

	//Girl* pGirl = Instantiate<Girl>(eLayerType::LT_NPC);
	//ShopBoy* pShopBoy = Instantiate<ShopBoy>(eLayerType::LT_NPC);

	//Portal* pPortal1 = Instantiate<Portal>(eLayerType::LT_OBJECT);
	//pPortal1->SetPos(Vec2(1980.f, 830.f));
	//pPortal1->Set_MovePos({ 86.f, 687.f });
	//pPortal1->Set_SceneName(L"Scene_Boss");
}

void Scene_Grandis::OnEnter()
{
	SoundMgr::Play(L"ChewChew");

	Camera::SetMinCameraPos(m_vMinCameraPos);
	Camera::SetMaxCameraPos(m_vMaxCameraPos);

	AddObj(s_pMainPlayer, eLayerType::LT_PLAYER);
	Camera::SetTarget(s_pMainPlayer);
	s_pMainPlayer->SetLimitPosX(m_vLimitPosX);
	s_pMainPlayer->SetPixelDC(m_pixelDC);
}

void Scene_Grandis::OnExit()
{
	SoundMgr::Stop(L"ChewChew");
	GetLayer(eLayerType::LT_PLAYER)->Release();
}

void Scene_Grandis::Init_Monster()
{
	RhyTurtle::SetPixelDC(m_pixelDC);
	RhyTurtle::SetRespawnTime(7.f);
	CT_RhyTurtle::SetPixelDC(m_pixelDC);
	CT_RhyTurtle::SetRespawnTime(7.f);

	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 140.f, 840.f });
}
