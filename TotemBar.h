#pragma once
#include "GameObject.h"

class JoTexture;

class TotemBar :
    public GameObject
{
public:
    TotemBar();
    ~TotemBar();

    void Initialize();
    void Update();
    void LateUpdate();
    void Render();

    int  Check_Bar();
    void Reset_Bar();

    void Set_Start();
    bool IsWait() { return m_bWait; }
private:
    JoTexture* m_pBarTex = nullptr;
    JoTexture* m_pSwordTex = nullptr;
    JoTexture* m_pRedGaugeTex = nullptr;
    JoTexture* m_pYellowGaugeTex = nullptr;

    Vec2 m_vBarPos{};
    Vec2 m_vSwordPos{};
    Vec2 m_vSwordLimit{};

    Vec2 m_vRedGauge{};
    Vec2 m_vLeftYellowGauge{};
    Vec2 m_vRightYellowGauge{};
    Vec2 m_vGaugeLimit{};

    Vec2 m_vEffectOffset{};

    float m_fSwordSpeed = 0.f;
    float m_fDir = 0.f;

    float m_fRedGaugeScale = 0.f;
    float m_fYellowGaugeScale = 0.f;

    bool m_bWait = false;
};

