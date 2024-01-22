#include "MyFmod.h"

FMOD::Studio::System* MyFmod::mSystem = nullptr;
FMOD::System* MyFmod::mCoreSystem = nullptr;
 
void MyFmod::Initialize()
{
	void* extraDriverData = nullptr;

	FMOD::Studio::System::create(&mSystem);

	mSystem->getCoreSystem(&mCoreSystem);
	mCoreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);

	mSystem->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
}

bool MyFmod::CreateSound(const std::string& path, FMOD::Sound** sound)
{
	if (FMOD_OK != mCoreSystem->createSound(path.c_str(), FMOD_3D, 0, sound))
		return false;

    return true;
}

void MyFmod::SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel)
{
	mCoreSystem->playSound(sound, 0, false, channel);

}

void MyFmod::Set3DListenerAttributes(const Vec2& pos)
{
	FMOD_VECTOR fmodPos(0.0f, 0.0f, 0.3f);
	FMOD_VECTOR fmodVel(0.0f, 0.0f, 0.0f);
	FMOD_VECTOR fmodForward(0.0f, 0.0f, 1.0f);
	FMOD_VECTOR fmodUp(0.0f, 1.0f, 0.0f);

	mCoreSystem->set3DListenerAttributes(0, &fmodPos, &fmodVel, &fmodForward, &fmodUp);
}

void MyFmod::Release()
{
	mSystem->release();
	mSystem = nullptr;
}
