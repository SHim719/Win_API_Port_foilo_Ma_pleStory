#include "Scene.h"
#include "Layer.h"
#include "MainGame.h"
#include "CollisionMgr.h"
#include "Player.h"

Player* Scene::s_pMainPlayer = nullptr;

extern MainGame g_MainGame;

Scene::Scene()
	: m_vLimitPosX{}
{
	createLayer();
}

Scene::~Scene()
{
	Release();
}

void Scene::Initialize()
{
	for (Layer* layer : m_vLayers)
		layer->Initialize();
}

void Scene::Update()
{
	for (Layer* layer : m_vLayers)
		layer->Update();
}

void Scene::LateUpdate()
{
	for (Layer* layer : m_vLayers)
		layer->LateUpdate();
}

void Scene::Render()
{
	for (Layer* layer : m_vLayers)
		layer->Render();
}

void Scene::Release()
{
	for (Layer* layer : m_vLayers)
		layer->Release();
}

void Scene::OnEnter()
{
}

void Scene::OnExit()
{
}

void Scene::Destroy()
{
	for (Layer* layer : m_vLayers)
		layer->Destroy();
}

void Scene::AddObj(GameObject* obj, const eLayerType& type)
{
	m_vLayers[(UINT)type]->AddObj(obj);
}

void Scene::CalcAndSetCameraArea(const float& fTexWidth, const float& fTexHeight, const Vec2& vOffset)
{
	float fHalfWidth = g_MainGame.GetWidth() * 0.5f;
	float fHalfHeight = g_MainGame.GetHeight() * 0.5f;

	m_vMinCameraPos.x = min(fHalfWidth, fTexWidth - fHalfWidth);
	m_vMinCameraPos.y = min(fHalfHeight, fTexHeight - fHalfHeight);
	m_vMaxCameraPos.x = max(fHalfWidth, fTexWidth - fHalfWidth);
	m_vMaxCameraPos.y = max(fHalfHeight, fTexHeight - fHalfHeight);
}

void Scene::Delete_DonDestroy()
{
	delete s_pMainPlayer;
	s_pMainPlayer = nullptr;
}

void Scene::createLayer()
{
	m_vLayers.resize((UINT)eLayerType::LT_END);
	for (size_t i = 0; i < (UINT)eLayerType::LT_END; ++i)
	{
		m_vLayers[i] = new Layer;
	}
}
