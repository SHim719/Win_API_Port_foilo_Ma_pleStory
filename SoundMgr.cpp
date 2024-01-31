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

	Audio* AbyssCave = ResourceMgr::Load<Audio>(L"AbyssCave", L"Resources/BGM/AbyssCave.mp3");
	AbyssCave->SetLoop(true);
	ResourceMgr::Load<Audio>(L"ChewChew", L"Resources/BGM/ChewChew WildWorld.mp3")->SetLoop(true);
	ResourceMgr::Load<Audio>(L"Nautilus", L"Resources/BGM/Nautilus.mp3")->SetLoop(true);
	ResourceMgr::Load<Audio>(L"TotemBGM", L"Resources/BGM/TotemBGM.mp3")->SetLoop(true);
	ResourceMgr::Load<Audio>(L"HenesysBGM", L"Resources/BGM/Henesys.mp3")->SetLoop(true);
	ResourceMgr::Load<Audio>(L"RudyBGM", L"Resources/BGM/RudyBGM.mp3")->SetLoop(true);
	ResourceMgr::Load<Audio>(L"RudyEndBGM", L"Resources/BGM/RudyEndBGM.mp3")->SetLoop(true);
	
	ResourceMgr::Load<Audio>(L"PB_Use", L"Resources/Skill/PhantomBlow/Use.mp3");
	ResourceMgr::Load<Audio>(L"PB_Hit_SFX", L"Resources/Skill/PhantomBlow/Hit.mp3");
	ResourceMgr::Load<Audio>(L"FJ_Use", L"Resources/Skill/FlashJump/Use.mp3");
	ResourceMgr::Load<Audio>(L"KF_Use", L"Resources/Skill/KarmaFury/Use.mp3");
	ResourceMgr::Load<Audio>(L"KF_Hit_SFX", L"Resources/Skill/KarmaFury/Hit.mp3");
	ResourceMgr::Load<Audio>(L"BT_Use", L"Resources/Skill/BladeTornado/Use.mp3");
	ResourceMgr::Load<Audio>(L"BT_Loop", L"Resources/Skill/BladeTornado/Loop.mp3");
	ResourceMgr::Load<Audio>(L"BT_Hit_SFX", L"Resources/Skill/BladeTornado/Hit.mp3");
	ResourceMgr::Load<Audio>(L"BS_Loop", L"Resources/Skill/BladeStorm/Loop.mp3")->SetLoop(true);
	ResourceMgr::Load<Audio>(L"BS_Hit_SFX", L"Resources/Skill/BladeStorm/Hit.mp3");
	ResourceMgr::Load<Audio>(L"AS_Loop", L"Resources/Skill/Asura/Loop.mp3")->SetLoop(true);
	ResourceMgr::Load<Audio>(L"AS_Hit_SFX", L"Resources/Skill/Asura/Hit.mp3");

	ResourceMgr::Load<Audio>(L"OpenWindow", L"Resources/UI/Sound/OpenWindow.mp3");
	ResourceMgr::Load<Audio>(L"CloseWindow", L"Resources/UI/Sound/CloseWindow.mp3");
	ResourceMgr::Load<Audio>(L"Slot_Click", L"Resources/UI/Sound/Click_Slot.MP3");
	ResourceMgr::Load<Audio>(L"Released_Picked", L"Resources/UI/Sound/Release_Picked.MP3");
	ResourceMgr::Load<Audio>(L"Tab_Click", L"Resources/UI/Sound/InvenTab.mp3");
	ResourceMgr::Load<Audio>(L"Bt_Click", L"Resources/UI/Sound/BtMouseClick.wav");
	ResourceMgr::Load<Audio>(L"esc", L"Resources/UI/Sound/esc.MP3");
	ResourceMgr::Load<Audio>(L"Use_Potion", L"Resources/UI/Sound/Use_Potion.mp3");
	ResourceMgr::Load<Audio>(L"Portal_SFX", L"Resources/SFX/Portal.MP3");
	ResourceMgr::Load<Audio>(L"Obtain_SFX", L"Resources/SFX/Obtain.mp3");
	ResourceMgr::Load<Audio>(L"Release_Item", L"Resources/SFX/Release_Item.MP3");
	ResourceMgr::Load<Audio>(L"Light", L"Resources/SFX/Light.mp3");
	ResourceMgr::Load<Audio>(L"LevelUp_SFX", L"Resources/SFX/LevelUp.mp3");

	ResourceMgr::Load<Audio>(L"Player_Jump", L"Resources/Player/Jump.mp3");
	ResourceMgr::Load<Audio>(L"Player_Dead", L"Resources/SFX/Dead.MP3");

	ResourceMgr::Load<Audio>(L"Vellum_Attack1", L"Resources/Enemy/Vellum/Sound/Attack1.mp3");
	ResourceMgr::Load<Audio>(L"Vellum_Attack2", L"Resources/Enemy/Vellum/Sound/Attack2.mp3");
	ResourceMgr::Load<Audio>(L"Vellum_Attack4", L"Resources/Enemy/Vellum/Sound/Attack4.mp3");
	ResourceMgr::Load<Audio>(L"Vellum_Attack5", L"Resources/Enemy/Vellum/Sound/Attack5.mp3");
	ResourceMgr::Load<Audio>(L"Vellum_Attack6", L"Resources/Enemy/Vellum/Sound/Attack6.mp3");
	ResourceMgr::Load<Audio>(L"Vellum_Attack7", L"Resources/Enemy/Vellum/Sound/Attack7.mp3");
	ResourceMgr::Load<Audio>(L"Vellum_Attack8", L"Resources/Enemy/Vellum/Sound/Attack8.mp3");
	ResourceMgr::Load<Audio>(L"Vellum_Attack9", L"Resources/Enemy/Vellum/Sound/Attack9.mp3");
	ResourceMgr::Load<Audio>(L"Vellum_Attack10", L"Resources/Enemy/Vellum/Sound/Attack10.mp3");
	ResourceMgr::Load<Audio>(L"Vellum_Attack11", L"Resources/Enemy/Vellum/Sound/Attack11.mp3");
	ResourceMgr::Load<Audio>(L"Vellum_Die", L"Resources/Enemy/Vellum/Sound/Die.mp3");
	ResourceMgr::Load<Audio>(L"Rhyno_Attack", L"Resources/Enemy/RhyTurtle/Attack.mp3");
	ResourceMgr::Load<Audio>(L"Rhyno_Die", L"Resources/Enemy/RhyTurtle/Die.mp3");
	ResourceMgr::Load<Audio>(L"Pirate_Attack", L"Resources/Enemy/DualPirate/Attack.mp3");
	ResourceMgr::Load<Audio>(L"Pirate_Hit", L"Resources/Enemy/DualPirate/Damaged.mp3");
	ResourceMgr::Load<Audio>(L"Pirate_Die", L"Resources/Enemy/DualPirate/Die.mp3");
	
	ResourceMgr::Load<Audio>(L"Aim_Shot", L"Resources/SFX/Shot.mp3");

	ResourceMgr::Load<Audio>(L"Slash1", L"Resources/Effect/TotemSlash/Single/Use.mp3");
	ResourceMgr::Load<Audio>(L"Slash2", L"Resources/Effect/TotemSlash/Double/Use.mp3");
	ResourceMgr::Load<Audio>(L"Slash4", L"Resources/Effect/TotemSlash/Triple/Use.mp3");
	ResourceMgr::Load<Audio>(L"Perfect_SFX", L"Resources/SFX/Perfect.mp3");
	ResourceMgr::Load<Audio>(L"Totem_Die_SFX", L"Resources/SFX/Totem_Die.mp3");
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

void SoundMgr::SetVolume(const wstring& _sName , const float& _fVolume)
{
	Audio* pAudio = ResourceMgr::Find<Audio>(_sName);

	if (pAudio == nullptr)
		return;

	pAudio->SetVolume(_fVolume);
}



