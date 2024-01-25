#include "Scene_Boss.h"
#include "AbyssCaveBG.h"
#include "joObject.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "Camera.h"
#include "SoundMgr.h"
#include "Vellum.h"
#include "VellumTrigger.h"
#include "StoneSpawner.h"
#include "DeepBreath.h"


Scene_Boss::Scene_Boss()
{
}

Scene_Boss::~Scene_Boss()
{
}

void Scene_Boss::Initialize()
{
	AbyssCaveBG* pBG = Instantiate<AbyssCaveBG>(eLayerType::LT_BACKGROUND);
	JoTexture* bgTex = ResourceMgr::Find<JoTexture>(L"BG_AbyssCave1");

	float texWidth = (float)bgTex->GetWidth();
	float texHeight = (float)bgTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight, Vec2::Zero);

	Vellum* pVellum = Instantiate<Vellum>(eLayerType::LT_MONSTER);
	pVellum->SetPos({ 1642.f, 370.f }); // 원래위치

	VellumTrigger* pVellumTrigger = Instantiate<VellumTrigger>(eLayerType::LT_NONE);
	pVellumTrigger->SetPos(Vec2(1642.f, 370.f));
	pVellumTrigger->Set_Vellum(pVellum);

	StoneSpawner* pStoneSpawner = Instantiate<StoneSpawner>(eLayerType::LT_NONE);
	pStoneSpawner->SetPlayer(s_pMainPlayer);

	m_vLimitPosX.x = 15.f;
	m_vLimitPosX.y = texWidth - 15.f;
	
	m_pixelDC = ResourceMgr::Find<JoBmp>(L"AbyssCave_Pixel")->Get_BmpDC();
}

void Scene_Boss::OnEnter()
{
	Camera::SetMinCameraPos(m_vMinCameraPos);
	Camera::SetMaxCameraPos(m_vMaxCameraPos);

	SoundMgr::Play(L"AbyssCave");

	AddObj(s_pMainPlayer, eLayerType::LT_PLAYER);
	Camera::SetTarget(s_pMainPlayer);
	s_pMainPlayer->SetLimitPosX(m_vLimitPosX);
	s_pMainPlayer->SetPixelDC(m_pixelDC);

	s_pMainPlayer->SetPos({ 1642.f, 400.f } );
}

void Scene_Boss::OnExit()
{
	SoundMgr::Stop(L"AbyssCave");
	GetLayer(eLayerType::LT_PLAYER)->Release();
}
