#include "SceneMgr.h"
#include "Scene_Title.h"

map<const wstring, Scene*> SceneMgr::m_mScenes = {};
Scene* SceneMgr::m_ActiveScene = nullptr;

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

