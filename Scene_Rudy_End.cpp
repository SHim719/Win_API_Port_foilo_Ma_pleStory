#include "Scene_Rudy_End.h"
#include "Camera.h"
#include "Player.h"
#include "BackGround.h"
#include "ResourceMgr.h"
#include "Totem_Player.h"
#include "SoundMgr.h"
#include "joObject.h"
#include "Stone.h"
#include "Item_Obj.h"
#include "UIMgr.h"

void Scene_Rudy_End::Initialize()
{
	m_vLimitPosX.x = 40.f;
	m_vLimitPosX.y = 4141.f;

	//Totem_Pixel
	JoTexture* pBGTex = ResourceMgr::Find<JoTexture>(L"BG_RudyEnd");
	BackGround* pBG = Instantiate<BackGround>(eLayerType::LT_BACKGROUND);
	pBG->SetBgTex(pBGTex);

	m_pixelDC = ResourceMgr::Find<JoBmp>(L"RudyEnd_Pixel")->Get_BmpDC();

	float texWidth = (float)pBGTex->GetWidth();
	float texHeight = (float)pBGTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight - 50.f, Vec2::Zero);

	Instantiate<Stone>(eLayerType::LT_NPC);
}

void Scene_Rudy_End::OnEnter()
{
	SoundMgr::Play(L"RudyEndBGM");
	Camera::SetMinCameraPos(m_vMinCameraPos);
	Camera::SetMaxCameraPos(m_vMaxCameraPos);

	AddObj(s_pMainPlayer, eLayerType::LT_PLAYER);
	Camera::SetTarget(s_pMainPlayer);
	Camera::SetLookAt(s_pMainPlayer->GetPos());
	s_pMainPlayer->SetLimitPosX(m_vLimitPosX);
	s_pMainPlayer->SetPixelDC(m_pixelDC);

	Item_Obj::SetPixel(m_pixelDC);

	UIMgr::SetCanUseUI(true);
}

void Scene_Rudy_End::OnExit()
{
	SoundMgr::Stop(L"RudyEndBGM");
	GetLayer(eLayerType::LT_PLAYER)->Release();
}
