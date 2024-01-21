#include "Scene_Title.h"
#include "Camera.h"
#include "BackGround.h"
#include "GiantRootBG.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "Girl.h"
#include "ShopBoy.h"


Scene_Title::Scene_Title()
{
}

Scene_Title::~Scene_Title()
{
}

void Scene_Title::Initialize()
{
	m_vLimitPosX.x = 233.f;
	m_vLimitPosX.y = 2283.f;

	Camera* pCamera = Instantiate<Camera>(eLayerType::LT_CAMERA);
	camera::pMainCamera = pCamera;

	GiantRootBG* pBg = Instantiate<GiantRootBG>(eLayerType::LT_BACKGROUND);
	JoTexture* bgTex = ResourceMgr::Find<JoTexture>(L"BG_GiantRoot1");

	float texWidth = (float)bgTex->GetWidth();
	float texHeight = (float)bgTex->GetHeight();
	CalcAndSetCameraArea(texWidth, texHeight, Vec2::Zero);
	pCamera->SetMinCameraPos(m_vMinCameraPos);
	pCamera->SetMaxCameraPos(m_vMaxCameraPos);

	Player* pPlayer = Instantiate<Player>(eLayerType::LT_PLAYER);
	pPlayer->SetPos({300.f, 200.f});
	pPlayer->SetLimitPosX(m_vLimitPosX);

	pCamera->SetTarget(pPlayer);

	m_pixelDC = ResourceMgr::Find<JoBmp>(L"GiantRoot_Pixel")->Get_BmpDC();
	pPlayer->SetPixelDC(m_pixelDC);

	Girl* pGirl = Instantiate<Girl>(eLayerType::LT_NPC);
	ShopBoy* pShopBoy = Instantiate<ShopBoy>(eLayerType::LT_NPC);
}


void Scene_Title::OnEnter()
{
}

void Scene_Title::OnExit()
{
}
