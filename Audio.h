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
    void PlayByChannels();
    void Stop();
    void SetVolume(const float& _fVolume);
    void SetLoop(const bool& _bLoop) { m_bLoop = _bLoop; }
private:
    FMOD::Sound* m_pSound;
    FMOD::Channel* m_pChannel;
    bool m_bLoop;

    vector<int> m_vecChannels = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int m_iChannel = 0;
};

