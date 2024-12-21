#pragma once
#include "GameObject.h"

class TotemBar;

class PerfectEffect :
    public GameObject
{
public:
    PerfectEffect();
    ~PerfectEffect();

    void Initialize()   override;
    void Update()   override;
    void Render()   override;

    void Set_TotemBar(TotemBar* _pTotemBar) { m_pTotemBar = _pTotemBar; }

private:
    void ResetBar();

private:
    TotemBar* m_pTotemBar = nullptr;
};

