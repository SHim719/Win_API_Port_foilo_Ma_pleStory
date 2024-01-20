#include "TimeMgr.h"
#include "MainGame.h"
#include "KeyMgr.h"


LARGE_INTEGER TimeMgr::cpuFrequency{};
LARGE_INTEGER TimeMgr::prevFrequency{};
LARGE_INTEGER TimeMgr::currentFrequency{};
float TimeMgr::fDeltaTime = 0.0f;
float TimeMgr::fps = 0.0f;

extern MainGame g_MainGame;

void TimeMgr::Initialize()
{
	// CPU 고유 진동수(1초에 진동하는 횟수)
	QueryPerformanceFrequency(&cpuFrequency);

	// 컴퓨터를 시작했을 때부터 진동수
	QueryPerformanceCounter(&prevFrequency);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&currentFrequency);

	float diffFrequency
		= static_cast<float>(currentFrequency.QuadPart - prevFrequency.QuadPart);

	float f = diffFrequency / static_cast<float>(cpuFrequency.QuadPart);
	fps = 1.0f / f;


	fDeltaTime = f;
	prevFrequency.QuadPart = currentFrequency.QuadPart;
}

void TimeMgr::Render()
{
	static float fTime = 0.0f;
	static int iFPS = 0;

	fTime += fDeltaTime;
	iFPS++;
	if (fTime >= 1.f)
	{
		//역수
		//float fps = 1.0f / fDeltaTime;

		Vec2 vWorldMousePos = KeyMgr::GetWorldMousePos();

		WCHAR str[50] = L"";
		swprintf_s(str, 50, L"FPS: %d X: %f Y: %f", iFPS, vWorldMousePos.x, vWorldMousePos.y);
		size_t len = wcsnlen_s(str, 50);

		SetWindowText(g_MainGame.GetHwnd(), str);// (_dc, 0, 0, str, (int)len);
		iFPS = 0;
		fTime = 0.f;
	}
	
}
