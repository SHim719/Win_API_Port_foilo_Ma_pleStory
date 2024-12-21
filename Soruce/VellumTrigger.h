#pragma once
#include "GameObject.h"

class Vellum;
class StoneSpawner;
class Vellum_HpBar;

class VellumTrigger :
    public GameObject
{
public:
    VellumTrigger();
    ~VellumTrigger();

    void Initialize() override;
    void Update()   override;
    void Render()   override;

    void Set_Vellum(Vellum* const _pVellum) { m_pVellum = _pVellum; }
    void Set_Spawnwer(StoneSpawner* const _pSpawner) { m_pSpawner = _pSpawner; }
    void Set_HpBar(Vellum_HpBar* const _pHpBar) { m_pHpBar = _pHpBar; }
private:
    Vellum* m_pVellum;
    StoneSpawner* m_pSpawner;
    Vellum_HpBar* m_pHpBar;
};

