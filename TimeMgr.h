#pragma once

#include "CommonInclude.h"


class TimeMgr
{
public:
	static void Initialize();
	static void Update();
	static void Render();

	static __forceinline float DeltaTime() { return fDeltaTime; }

	static float fps;

private:
	static LARGE_INTEGER cpuFrequency;
	static LARGE_INTEGER prevFrequency;
	static LARGE_INTEGER currentFrequency;
	static float fDeltaTime;
};

