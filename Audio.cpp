#include "Audio.h"

Audio::Audio()
	: JoResource(eResourceType::Audio)
	, m_pSound(nullptr)
	, m_pChannel(nullptr)
	, m_bLoop(false)
{
}

Audio::~Audio()
{
	m_pSound->release();
	m_pSound = nullptr;
}

HRESULT Audio::Load(const wstring& path)
{
	string cPath(path.begin(), path.end());
	if (!MyFmod::CreateSound(cPath, &m_pSound))
		return S_FALSE;

	return S_OK;
}

void Audio::Play()
{
	if (m_bLoop)
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	else
		m_pSound->setMode(FMOD_LOOP_OFF);

	MyFmod::SoundPlay(m_pSound, &m_pChannel);
}

void Audio::Stop()
{
	m_pChannel->stop();
}

void Audio::SetVolume(const float& _fVolume)
{
	m_pChannel->setVolume(_fVolume);
}
