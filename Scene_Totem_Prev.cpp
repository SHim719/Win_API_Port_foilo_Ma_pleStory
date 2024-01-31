#include "Scene_Totem_Prev.h"
#include "MainGame.h"
#include "Camera.h"
#include "Player.h"
#include "BackGround.h"
#include "ResourceMgr.h"
#include "Totem_Player.h"
#include "SoundMgr.h"
#include "joObject.h"
#include "Frieto.h"

Scene_Totem_Prev::Scene_Totem_Prev()
{
}

Scene_Totem_Prev::~Scene_Totem_Prev()
{
}

void Scene_Totem_Prev::Initialize()
{
	//Totem_Pixel
	JoTexture* pBGTex = ResourceMgr::Find<JoTexture>(L"BG_Totem");
	BackGround* pBG = Instantiate<BackGround>(eLayerType::LT_BACKGROUND);
	pBG->SetBgTex(pBGTex);

	m_pixelDC = ResourceMgr::Find<JoBmp>(L"Totem_Pixel")->Get_BmpDC();

	float texWidth = (float)pBGTex->GetWidth();
	float texHeight = (float)pBGTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight, Vec2::Zero);

	Frieto* pFrieto = Instantiate<Frieto>(eLayerType::LT_NPC);


}

void Scene_Totem_Prev::OnEnter()
{
	AddObj(s_pMainPlayer, eLayerType::LT_PLAYER);
	Camera::SetTarget(s_pMainPlayer);
	Camera::SetLookAt(s_pMainPlayer->GetPos());
	Camera::Set_NoLimit(false);
	s_pMainPlayer->SetLimitPosX(m_vLimitPosX);
	s_pMainPlayer->SetPixelDC(m_pixelDC);
	SoundMgr::Play(L"TotemBGM");
}

void Scene_Totem_Prev::OnExit()
{
	SoundMgr::Stop(L"TotemBGM");
	GetLayer(eLayerType::LT_PLAYER)->Release();
}
