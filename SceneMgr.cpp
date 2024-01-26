#include "SceneMgr.h"
#include "Scene_Title.h"
#include "Scene_Rutabyss.h"
#include "Scene_Boss.h"

map<const wstring, Scene*> SceneMgr::m_mScenes = {};
Scene* SceneMgr::m_ActiveScene = nullptr;
Scene* SceneMgr::m_pNextScene = nullptr;

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
	SceneMgr::CreateScene<Scene_Boss>(L"Scene_Boss");
	

	SceneMgr::LoadScene(L"Scene_Title");
}

void SceneMgr::Update()
{
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

void SceneMgr::Reservation_ChangeScene(const wstring& _wsName)
{
	auto it = m_mScenes.find(_wsName);
	if (it == m_mScenes.end())
		return;

	m_pNextScene = it->second;
}

void SceneMgr::ChangeScene()
{
	if (m_pNextScene == nullptr)
		return;

	m_ActiveScene->OnExit();

	m_ActiveScene = m_pNextScene;
	m_ActiveScene->OnEnter();

	m_pNextScene = nullptr;
}

