#pragma once

#include "JoResource.h"
#include "MyFmod.h"


class Audio :
    public JoResource
{
public:
    Audio();
    ~Audio();

    HRESULT Load(const wstring& path) override;
    void Play();
    void Stop();
    void SetVolume(const float& _fVolume);
    void SetLoop(const bool& _bLoop) { m_bLoop = _bLoop; }
private:
    FMOD::Sound* m_pSound;
    FMOD::Channel* m_pChannel;
    bool m_bLoop;
};

