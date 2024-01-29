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

    float m_fSwordSpeed = 0.f;
    float m_fDir = 0.f;

    float m_fRedGaugeScale = 0.f;
    float m_fYellowGaugeScale = 0.f;
};

