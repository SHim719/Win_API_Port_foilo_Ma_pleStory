#include "Scene_Rudy.h"
#include "Camera.h"
#include "Player.h"
#include "RudyBG.h"
#include "ResourceMgr.h"
#include "SoundMgr.h"
#include "joObject.h"
#include "Portal.h"
#include "DualPirate.h"
#include "MiniMap.h"
#include "YellowPortal.h"
#include "EventPortal2.h"
#include "Item_Obj.h"

void Scene_Rudy::Initialize()
{
	m_vLimitPosX.x = 20.f;
	m_vLimitPosX.y = 2100.f;

	RudyBG* pBg = Instantiate<RudyBG>(eLayerType::LT_BACKGROUND);
	JoTexture* bgTex = ResourceMgr::Find<JoTexture>(L"BG_Rudy1");
	float texWidth = (float)bgTex->GetWidth();
	float texHeight = (float)bgTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight - 100.f, Vec2::Zero);

	m_pixelDC = ResourceMgr::Find<JoBmp>(L"Rudy_Pixel")->Get_BmpDC();

	DualPirate::SetRespawnTime(10.f);
	DualPirate::SetPixelDC(m_pixelDC);

	MiniMap* pMiniMap = Instantiate<MiniMap>(eLayerType::LT_UI);
	JoTexture* pMiniMapTex = ResourceMgr::Find<JoTexture>(L"Rudy_Minimap");
	pMiniMap->Set_MiniMapTex(pMiniMapTex);
	pMiniMap->SetSize({ 166.f, 226.f });
	pMiniMap->SetLeftTop({ 25.f, 56.f });
	pMiniMap->SetRealMapSize({ texWidth, texHeight });

	/*Portal* pPortal1 = Instantiate<Portal>(eLayerType::LT_OBJECT);
	pPortal1->SetPos(Vec2(500.f, 830.f));
	pPortal1->Set_MovePos({ 120.f, 840.f });
	pPortal1->Set_SceneName(L"Scene_Grandis");*/

	YellowPortal* pYellowPortal1 = Instantiate<YellowPortal>(eLayerType::LT_OBJECT);
	pYellowPortal1->SetPos({ 1050.f, 308.f });
	pYellowPortal1->Set_MovePos({ 1050.f, 2620.f });

	YellowPortal* pYellowPortal2 = Instantiate<YellowPortal>(eLayerType::LT_OBJECT);
	pYellowPortal2->SetPos({ 1050.f,  2620.f });
	pYellowPortal2->Set_MovePos({ 1050.f, 308.f });

	//EventPortal 2000, 2634
	EventPortal2* pEventPortal = Instantiate<EventPortal2>(eLayerType::LT_OBJECT);
	pEventPortal->SetPos({ 2000.f, 2634.f });
	pEventPortal->Set_MovePos({ 217.f, 650.f });
	pEventPortal->Set_SceneName(L"Scene_RudyEnd");

	Init_Monster();
}


void Scene_Rudy::OnEnter()
{
	SoundMgr::Play(L"RudyBGM");

	Camera::SetMinCameraPos(m_vMinCameraPos);
	Camera::SetMaxCameraPos(m_vMaxCameraPos);

	AddObj(s_pMainPlayer, eLayerType::LT_PLAYER);
	Camera::SetTarget(s_pMainPlayer);
	Camera::SetLookAt(s_pMainPlayer->GetPos());
	s_pMainPlayer->SetLimitPosX(m_vLimitPosX);
	s_pMainPlayer->SetPixelDC(m_pixelDC);
	Item_Obj::SetPixel(m_pixelDC);
}

void Scene_Rudy::OnExit()
{
	SoundMgr::Stop(L"RudyBGM");
	GetLayer(eLayerType::LT_PLAYER)->Release();
}

void Scene_Rudy::Init_Monster()
{
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1329.f, 486.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1730.f, 486.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 397.f, 1330.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 590.f, 1330.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 690.f, 1330.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 870.f, 1330.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1380.f, 1330.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1500.f, 1330.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1672.f, 1330.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1472.f, 1330.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1710.f, 1730.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1330.f, 2115.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1558.f, 2115.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1829.f, 2115.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1703.f, 2612.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1409.f, 2612.f});
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 1000.f, 2612.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 854.f, 2622.f});
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 610.f, 2622.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 222.f, 2622.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 334.f, 2370.f});
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 100.f, 2370.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 476.f, 2119.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 750.f, 2119.f });
	Instantiate<DualPirate>(eLayerType::LT_MONSTER)->SetRespawnPos({ 395.f, 1763.f });

}
