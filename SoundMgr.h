#pragma once

#include "MyFmod.h"
#include "Audio.h"

class SoundMgr
{
public:
	static void Intialize();
	static void Play(const wstring& _sName);
	static void Stop(const wstring& _sName);

};

