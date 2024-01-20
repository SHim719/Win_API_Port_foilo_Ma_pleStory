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
	
	ResourceMgr::Load<Audio>(L"PB_Use", L"Resources/Skill/PhantomBlow/Use.mp3");
	ResourceMgr::Load<Audio>(L"PB_Hit", L"Resources/Skill/PhantomBlow/Hit.mp3");
	ResourceMgr::Load<Audio>(L"FJ_Use", L"Resources/Skill/FlashJump/Use.mp3");

	ResourceMgr::Load<Audio>(L"OpenWindow", L"Resources/UI/Sound/OpenWindow.mp3");
	ResourceMgr::Load<Audio>(L"CloseWindow", L"Resources/UI/Sound/CloseWindow.mp3");
	ResourceMgr::Load<Audio>(L"Slot_Click", L"Resources/UI/Sound/Click_Slot.MP3");
	ResourceMgr::Load<Audio>(L"Released_Picked", L"Resources/UI/Sound/Release_Picked.MP3");
	ResourceMgr::Load<Audio>(L"Tab_Click", L"Resources/UI/Sound/InvenTab.mp3");
	ResourceMgr::Load<Audio>(L"Player_Jump", L"Resources/Player/Jump.mp3");


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



