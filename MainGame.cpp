#include "MainGame.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"
#include "RenderMgr.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "MyFmod.h"
#include "UIMgr.h"
#include "ItemDatabase.h"
#include "Camera.h"

MainGame::MainGame()
	: m_hwnd(nullptr)
	, m_dc(nullptr)
	, m_width(0)
	, m_height(0)
	, m_pCursorTex(nullptr)
{
}

MainGame::~MainGame()
{
}

void MainGame::Run()
{
	Update();
	LateUpdate();
	Render();
	SceneMgr::ChangeScene();
	SceneMgr::Destroy();
}

void MainGame::Initialize(HWND _hwnd, UINT _width, UINT _height)
{
	m_hwnd = _hwnd;
	m_dc = GetDC(m_hwnd);

	m_width = _width;
	m_height = _height;

	adjustWindowRect();
	ShowCursor(false);

	MyFmod::Initialize();
	KeyMgr::Initialize();
	RenderMgr::Initialize();
	ResourceMgr::Initialize();
	UIMgr::Initialize();
	ItemDatabase::Initialize();
	SoundMgr::Intialize();
	SceneMgr::Initialize();
	CollisionMgr::Initialize();
	Camera::Initialize();
	TimeMgr::Initialize();
	

	m_pCursorTex = ResourceMgr::Find<JoTexture>(L"Cursor");
}

void MainGame::Update()
{
	TimeMgr::Update();
	KeyMgr::Update();
	SceneMgr::Update();
	Camera::Update();
	CollisionMgr::Update();
	UIMgr::Update();
}

void MainGame::LateUpdate()
{
	SceneMgr::LateUpdate();
}

void MainGame::Render()
{
	RenderMgr::GetRenderTarget()->BeginDraw();
	SceneMgr::Render();
	UIMgr::Render();
	render_cursor();
	Camera::Render();
	RenderMgr::GetRenderTarget()->EndDraw();
	TimeMgr::Render();
}

void MainGame::adjustWindowRect()
{
	RECT rect = { 0, 0, (LONG)m_width, (LONG)m_height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(m_hwnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0);
}

void MainGame::render_cursor()
{
	if (!m_bCursorRender)
		return;
	
	Vec2 vMousePos = KeyMgr::GetMousePos();
	RenderMgr::RenderImage(m_pCursorTex
		, vMousePos.x
		, vMousePos.y
		, vMousePos.x + 24.f
		, vMousePos.y + 28.f);
}
