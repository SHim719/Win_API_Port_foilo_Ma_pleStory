#include "Scene_Totem_Prev.h"
#include "MainGame.h"
#include "Camera.h"
#include "Player.h"
#include "BackGround.h"
#include "ResourceMgr.h"
#include "SoundMgr.h"
#include "joObject.h"
#include "Esfesia.h"
#include "Portal.h"
#include "Item_Obj.h"


Scene_Totem_Prev::Scene_Totem_Prev()
{
}

Scene_Totem_Prev::~Scene_Totem_Prev()
{
}

void Scene_Totem_Prev::Initialize()
{
	m_vLimitPosX.x = 0.f;
	m_vLimitPosX.y = 1349.f;

	JoTexture* pBGTex = ResourceMgr::Find<JoTexture>(L"BG_Totem");
	BackGround* pBG = Instantiate<BackGround>(eLayerType::LT_BACKGROUND);
	pBG->SetBgTex(pBGTex);

	m_pixelDC = ResourceMgr::Find<JoBmp>(L"Totem_Pixel")->Get_BmpDC();

	float texWidth = (float)pBGTex->GetWidth();
	float texHeight = (float)pBGTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight, Vec2::Zero);

	Portal* pPortal = Instantiate<Portal>(eLayerType::LT_OBJECT);
	pPortal->SetPos( { 158.f, 552.f });
	pPortal->Set_MovePos(Vec2(1502.f, 830.f));
	pPortal->Set_SceneName(L"Scene_Rutabyss");

	Esfesia* pEsfesia = Instantiate<Esfesia>(eLayerType::LT_NPC);
}

void Scene_Totem_Prev::OnEnter()
{
	AddObj(s_pMainPlayer, eLayerType::LT_PLAYER);

	Camera::SetMinCameraPos(m_vMinCameraPos);
	Camera::SetMaxCameraPos(m_vMaxCameraPos);
	Camera::SetTarget(s_pMainPlayer);
	Camera::SetLookAt(s_pMainPlayer->GetPos());
	Camera::Set_NoLimit(false);

	s_pMainPlayer->SetLimitPosX(m_vLimitPosX);
	s_pMainPlayer->SetPixelDC(m_pixelDC);
	Item_Obj::SetPixel(m_pixelDC);
	SoundMgr::Play(L"TotemBGM");
}

void Scene_Totem_Prev::OnExit()
{
	SoundMgr::Stop(L"TotemBGM");
	GetLayer(eLayerType::LT_PLAYER)->Release();
}
