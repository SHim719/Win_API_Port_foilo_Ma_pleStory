#pragma once

#include "CommonInclude.h"


class TimeMgr
{
public:
	static void Initialize();
	static void Update();
	static void Render();

	static __forceinline float DeltaTime() { return fDeltaTime * fTimeScale; }
	static float DeltaTime_NoScale() { return fDeltaTime; }

	static float fps;

	static void SetTimeScale(float _fScale) { fTimeScale = _fScale; }
private:
	static LARGE_INTEGER cpuFrequency;
	static LARGE_INTEGER prevFrequency;
	static LARGE_INTEGER currentFrequency;
	static float fDeltaTime;
	static float fTimeScale;
};

