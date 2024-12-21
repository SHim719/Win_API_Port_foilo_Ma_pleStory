#pragma once
#include "GameObject.h"


class TimerUI :
    public GameObject
{
public:
    TimerUI();
    ~TimerUI();

    void Initialize()   override;
    void Update()       override;
    void Render()       override;

    void SetTime(float _fTime) { m_fTime = _fTime; }
    const float& GetTime() const { return m_fTime; }
private:
    JoTexture* m_pTimerTex = nullptr;
    JoTexture* m_pNumberTex = nullptr;

    float m_fTime = 0.f;
};

