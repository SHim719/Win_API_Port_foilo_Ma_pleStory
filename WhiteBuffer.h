#pragma once
#include "GameObject.h"


class WhiteBuffer :
    public GameObject
{
public:
    void Initialize();
    void Update();
    void Render();

    void Set_Fade(float _fInitAlpha, float _fSpeed, bool _bIncrease, bool _bNoDestroy = false);
private:
    JoTexture* m_pWhiteBuffer = nullptr;
    
    float m_fAlpha = 1.0f;
    float m_fSpeed = 0.f;
    bool m_bNoDestroy = false;
};

