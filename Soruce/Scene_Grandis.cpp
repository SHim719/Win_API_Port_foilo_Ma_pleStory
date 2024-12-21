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
#include "YellowPortal.h"
#include "MiniMap.h"
#include "Portal.h"
#include "EventPortal.h"
#include "Item_Obj.h"

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
	m_vLimitPosX.y = 5655.f;

	ChewBG* pBg = Instantiate<ChewBG>(eLayerType::LT_BACKGROUND);
	JoTexture* bgTex = ResourceMgr::Find<JoTexture>(L"BG_Chew1");

	float texWidth = (float)bgTex->GetWidth();
	float texHeight = (float)bgTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight, Vec2::Zero);

	MiniMap* pMiniMap = Instantiate<MiniMap>(eLayerType::LT_UI);
	JoTexture* pMiniMapTex = ResourceMgr::Find<JoTexture>(L"Chew_Minimap");
	pMiniMap->Set_MiniMapTex(pMiniMapTex);
	pMiniMap->SetSize({ 350.f, 48.f });
	pMiniMap->SetLeftTop({ 10.f, 61.f });
	pMiniMap->SetRealMapSize({ texWidth, texHeight });

	m_vMaxCameraPos.y -= 100.f;

	m_pixelDC = ResourceMgr::Find<JoBmp>(L"Chew_Pixel")->Get_BmpDC();

	RapidStream* pStream = Instantiate<RapidStream>(eLayerType::LT_OBJECT);

	YellowPortal* pYellowPortal = Instantiate<YellowPortal>(eLayerType::LT_OBJECT);
	pYellowPortal->SetPos({ 5400.f, 840.f });
	pYellowPortal->Set_MovePos({ 430.f, 852.f });

	Portal* pPortal = Instantiate<Portal>(eLayerType::LT_OBJECT);
	pPortal->SetPos(Vec2(247.f, 825.f));
	pPortal->Set_MovePos( {500.f, 830.f });
	pPortal->Set_SceneName(L"Scene_Rutabyss");

	EventPortal* pEventPortal = Instantiate<EventPortal>(eLayerType::LT_OBJECT);
	pEventPortal->SetPos({ 5624.f, 830.f });
	pEventPortal->Set_MovePos({ 200.f, 400.f });
	pEventPortal->Set_SceneName(L"Scene_Rudy");

	Init_Monster();
}

void Scene_Grandis::OnEnter()
{
	SoundMgr::Play(L"ChewChew");

	Camera::SetMinCameraPos(m_vMinCameraPos);
	Camera::SetMaxCameraPos(m_vMaxCameraPos);

	AddObj(s_pMainPlayer, eLayerType::LT_PLAYER);
	Camera::SetTarget(s_pMainPlayer);
	Camera::SetLookAt(s_pMainPlayer->GetPos());
	s_pMainPlayer->SetLimitPosX(m_vLimitPosX);
	s_pMainPlayer->SetPixelDC(m_pixelDC);

	Item_Obj::SetPixel(m_pixelDC);
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

	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 600.f, 840.f });
	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 700.f, 840.f });
	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 800.f, 845.f });

	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 755.f, 620.f });
	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 911.f, 620.f });

	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1025.f, 524.f });
	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1215.f, 524.f });

	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1135.f, 730.f });
	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1234.f, 730.f });

	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 2391.f, 698.f });
	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 2480.f, 698.f });

	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 2775.f, 601.f });
	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 2872.f, 601.f });

	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 3300.f, 620.f });
	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 3465.f, 620.f });

	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 2771.f, 847.f });
	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 2900.f, 847.f });
	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 3072.f, 847.f });
	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 3150.f, 847.f });

	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 4700.f, 617.f });
	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 4790.f, 617.f });

	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 5159.f, 730.f });
	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 5310.f, 730.f });

	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 4881.f, 858.f });
	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 5000.f, 858.f });
	Instantiate<CT_RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 5159.f, 858.f });
	Instantiate<RhyTurtle>(eLayerType::LT_MONSTER)->SetRespawnPos({ 5222.f, 858.f });

}
