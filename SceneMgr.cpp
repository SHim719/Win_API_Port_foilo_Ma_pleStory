#include "SceneMgr.h"
#include "Scene_Title.h"
#include "Scene_Rutabyss.h"
#include "Scene_Boss.h"
#include "Scene_Grandis.h"
#include "Scene_Eagle.h"
#include "Scene_Totem.h"
#include "Camera.h"

map<const wstring, Scene*> SceneMgr::m_mScenes = {};
Scene* SceneMgr::m_ActiveScene = nullptr;
Scene* SceneMgr::m_pNextScene = nullptr;
Vec2 SceneMgr::m_vMovePos{};

void SceneMgr::LoadScene(const wstring& name)
{
	if (m_ActiveScene != nullptr)
		m_ActiveScene->OnExit();

	auto it = m_mScenes.find(name);
	if (it == m_mScenes.end()) return;

	m_ActiveScene = it->second;
	m_ActiveScene->OnEnter();
}

void SceneMgr::Initialize()
{
	SceneMgr::CreateScene<Scene_Title>(L"Scene_Title");
	SceneMgr::CreateScene<Scene_Rutabyss>(L"Scene_Rutabyss");
	SceneMgr::CreateScene<Scene_Grandis>(L"Scene_Grandis");
	SceneMgr::CreateScene<Scene_Boss>(L"Scene_Boss");
	SceneMgr::CreateScene<Scene_Eagle>(L"Scene_Eagle");
	SceneMgr::CreateScene<Scene_Totem>(L"Scene_Totem");
	
	SceneMgr::LoadScene(L"Scene_Title");
}

void SceneMgr::Update()
{
	if (false == IsChangingScene())
		m_ActiveScene->Update();
}

void SceneMgr::LateUpdate()
{
	m_ActiveScene->LateUpdate();
}

void SceneMgr::Render()
{
	m_ActiveScene->Render();
}

void SceneMgr::Destroy()
{
	m_ActiveScene->Destroy();
}

void SceneMgr::Release()
{
	Scene::Delete_DonDestroy();
}

void SceneMgr::Reservation_ChangeScene(const wstring& _wsName, const Vec2& _vMovePos)
{
	auto it = m_mScenes.find(_wsName);
	if (it == m_mScenes.end())
		return;

	m_vMovePos = _vMovePos;

	Camera::Set_FadeOut(1.f, 0.f, true);

	m_pNextScene = it->second;
}

bool SceneMgr::ChangeScene()
{
	if (m_pNextScene == nullptr)
		return false;

	if (Camera::IsFadeOut())
		return true;

	Camera::Set_FadeIn(2.f, 1.f, true);

	m_ActiveScene->OnExit();

	m_ActiveScene = m_pNextScene;
	m_ActiveScene->Set_PlayerPos(m_vMovePos);
	m_ActiveScene->OnEnter();

	m_pNextScene = nullptr;

	return false;
}

