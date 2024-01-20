#include "SoundMgr.h"
#include "MyFmod.h"
#include "Audio.h"
#include "ResourceMgr.h"


void SoundMgr::Intialize()
{
	Audio* titleBGM = ResourceMgr::Load<Audio>(L"TitleBGM", L"Resources/BGM/Title.mp3");
	titleBGM->SetLoop(true);

	Audio* GiantRoot = ResourceMgr::Load<Audio>(L"GiantRoot", L"Resources/BGM/YggdrasilPrayer.mp3");
	GiantRoot->SetLoop(true);
	
	Audio* phantom_use = ResourceMgr::Load<Audio>(L"PB_Use", L"Resources/Skill/PhantomBlow/Use.mp3");
	Audio* phantom_hit = ResourceMgr::Load<Audio>(L"PB_Hit", L"Resources/Skill/PhantomBlow/Hit.mp3");

	//GiantRoot->Play();
}

void SoundMgr::Play(const wstring& _sName)
{
	Audio* pAudio = ResourceMgr::Find<Audio>(_sName);

	if (pAudio == nullptr)
		return;

	pAudio->Play();
}

void SoundMgr::Stop(const wstring& _sName)
{
	Audio* pAudio = ResourceMgr::Find<Audio>(_sName);

	if (pAudio == nullptr)
		return;

	pAudio->Stop();
}



